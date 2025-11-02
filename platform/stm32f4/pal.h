
#ifndef PAL_HOST_H
#define PAL_HOST_H

#include <stdint.h>

uint32_t pal_millis(void);

void pal_delay_ms(uint32_t ms);
void pal_critical_enter(void);

void pal_critical_exit(void);

void pal_start(void);

#endif