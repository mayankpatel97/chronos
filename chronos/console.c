#include "console.h"
#include "stm32f4xx.h"
#include <stdio.h>


int (*console_putc)(char);

/*
    int console_putc(char c) {
        while (!(USART2->SR & USART_SR_TXE));
        USART2->DR = c;
        return c;
    }
*/

void console_init(int (*ptr)(char c))
{
    /* already done in pal_init */ 
    console_putc = ptr;
}

int console_printf(const char *fmt, ...)
{
    if(console_putc == NULL) return -1;
    char buf[128];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    for (int i = 0; i < n; i++) console_putc(buf[i]);
    return n;
}
