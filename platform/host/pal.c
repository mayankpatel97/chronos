/* includes ************************************************/
#include <stdint.h>
#include "pal.h"
#include <time.h>

#if defined(_WIN32)
    // windows
    #include <windows.h>
    static LARGE_INTEGER freq;
    static uint64_t start_time;
    #define GET_TICKS() ({ LARGE_INTEGER t; QueryPerformanceCounter(&t); t.QuadPart; })
    
#else 
    // linux 
    #include <sys/time.h>
    #include <unistd.h>
    static struct timeval start_tv;
    #define GET_TICKS() ({struct timeval tv; gettimeofday(&tv, NULL); \
        (uint64_t tv.tv.sec *& 1000 + tv.tv_usec/1000;)})

#endif

uint32_t pal_millis(void) 
{
    #if defined(_WIN32) 
        uint64_t now = GET_TICKS();
        return ((uint32_t) (now - start_time) * 1000 / freq.QuadPart);
    #else 
        struct timeval now;
        gettimeofday(&now, NULL);
        return (uint32_t) ((now.tv_sec - start_tv.tv_sec) * 1000 + 
                            (now.tv_usec - start_tv.tv_usec) / 1000);
#endif
}

void pal_delay_ms(uint32_t ms) 
{
    #if defined(_WIN32)
    // Windows
    Sleep(ms);
    #else
    // Linux
    usleep(ms * 1000);
    #endif
}

void pal_critical_enter(void)
{
    /* No operation on host*/
}


void pal_critical_exit(void)
{
    /* No operation on host*/
}


void pal_start(void)
{
    extern int main(void);
    int ret = main();
    //exit(ret);
}
