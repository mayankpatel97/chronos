#ifndef CHRONOS_H
#define CHRONOS_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Configurable parameters. Adjust if needed.
 */
#ifndef CHRONOS_MAX_TASKS
#define CHRONOS_MAX_TASKS   12   // enough for most small apps
#endif

#ifndef CHRONOS_TICK_HZ
#define CHRONOS_TICK_HZ     1000 // SysTick frequency in Hz
#endif

// Task handle
typedef int chronos_task_t;
#define CHRONOS_INVALID_TASK   (-1)

// Init internal state (call once)
void chronos_init(void);

// Call this from SysTick interrupt
void chronos_tick(void);

// Cooperative scheduler loop (never returns)
void chronos_run(void);

// Current time in ms (wraps)
uint32_t chronos_millis(void);

// Schedule a function call
// period_ms = how often it runs (0 = run once)
// delay_ms = initial delay before first call
chronos_task_t chronos_add(void (*fn)(void *arg), void *arg,
                           uint32_t period_ms, uint32_t delay_ms);

// Enable / Disable existing task
bool chronos_enable(chronos_task_t h, bool en);

// Remove task completely
bool chronos_cancel(chronos_task_t h);

#endif
