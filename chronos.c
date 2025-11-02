#include "chronos.h"
#include "main.h"   // for __WFI() and core definitions
#include <string.h>

/*
 * Each task is stored here.
 * No dynamic allocation. Just fixed slots.
 */
typedef struct {
    void (*fn)(void *arg);
    void *arg;
    uint32_t period;
    uint32_t next_deadline;
    uint8_t used;
    uint8_t enabled;
} task_t;

static volatile uint32_t g_time_ms = 0;
static task_t tasks[CHRONOS_MAX_TASKS];

/*
 * Disable interrupts (just PRIMASK).
 * Simple and enough for STM32F4.
 */
static inline uint32_t lock(void)
{
    uint32_t pm;
    __asm volatile("MRS %0, PRIMASK" : "=r"(pm));
    __asm volatile("cpsid i");
    return pm;
}

static inline void unlock(uint32_t pm)
{
    __asm volatile("MSR PRIMASK, %0" :: "r"(pm));
}

/*
 * Call once after clock + HAL init.
 */
void chronos_init(void)
{
    uint32_t pm = lock();
    g_time_ms = 0;
    memset(tasks, 0, sizeof(tasks));
    unlock(pm);
}

/*
 * Called from SysTick (1 kHz by default).
 */
void chronos_tick(void)
{
    g_time_ms++;
}

/*
 * Milliseconds since start.
 */
uint32_t chronos_millis(void)
{
    return g_time_ms;
}

/*
 * Add new task.
 */
chronos_task_t chronos_add(void (*fn)(void *), void *arg,
                           uint32_t period_ms, uint32_t delay_ms)
{
    if (!fn)
        return CHRONOS_INVALID_TASK;

    uint32_t pm = lock();
    for (int i = 0; i < CHRONOS_MAX_TASKS; i++) {
        if (!tasks[i].used) {
            tasks[i].used = 1;
            tasks[i].enabled = 1;
            tasks[i].fn = fn;
            tasks[i].arg = arg;
            tasks[i].period = period_ms;
            tasks[i].next_deadline = g_time_ms + delay_ms;
            unlock(pm);
            return i;
        }
    }
    unlock(pm);
    return CHRONOS_INVALID_TASK; // no free slot
}

/*
 * Turn on/off task without deleting.
 */
bool chronos_enable(chronos_task_t h, bool en)
{
    if (h < 0 || h >= CHRONOS_MAX_TASKS)
        return false;
    uint32_t pm = lock();
    if (tasks[h].used)
        tasks[h].enabled = en ? 1 : 0;
    unlock(pm);
    return true;
}

/*
 * Delete task permanently.
 */
bool chronos_cancel(chronos_task_t h)
{
    if (h < 0 || h >= CHRONOS_MAX_TASKS)
        return false;
    uint32_t pm = lock();
    memset(&tasks[h], 0, sizeof(task_t));
    unlock(pm);
    return true;
}

/*
 * Core scheduler loop.
 * Picks ready tasks and runs them.
 * Since this is cooperative, tasks should not block.
 */
void chronos_run(void)
{
    while (1) {

        uint32_t now = g_time_ms;
        bool did_run = false;

        for (int i = 0; i < CHRONOS_MAX_TASKS; i++) {

            if (!tasks[i].used || !tasks[i].enabled)
                continue;

            // Time to run?
            if ((int32_t)(now - tasks[i].next_deadline) >= 0) {

                void (*fn)(void *) = tasks[i].fn;
                void *arg = tasks[i].arg;
                uint32_t p = tasks[i].period;

                // Reschedule first so task can cancel itself safely
                if (p == 0) {
                    tasks[i].enabled = 0;
                } else {
                    tasks[i].next_deadline += p;
                }

                did_run = true;
                fn(arg);

                // If one-shot, remove it now
                if (p == 0) {
                    uint32_t pm = lock();
                    memset(&tasks[i], 0, sizeof(task_t));
                    unlock(pm);
                }
            }
        }

        // If nothing to do, wait for next tick (saves power)
        if (!did_run) {
            __WFI();
        }
    }
}
