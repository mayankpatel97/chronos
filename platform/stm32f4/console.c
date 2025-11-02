#include "console.h"
#include "stm32f4xx.h"
#include <stdio.h>

void console_init(void) { 
    /* already done in pal_init */ 
}

int console_putc(char c) {
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = c;
    return c;
}

int console_printf(const char *fmt, ...) {
    char buf[128];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    for (int i = 0; i < n; i++) console_putc(buf[i]);
    return n;
}