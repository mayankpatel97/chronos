#include "console.c"
#include <stdio.h>
#include <stdarg.h>

void console_init(void)
{
    /* Nothing needed in host*/
}

int console_putc(char c)
{
    return putchar(c);
}

int console_puts(const char *s)
{
    return fputs(s, stdout);
}

int console_print(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = vprintf(fmt, ap);
    va_end(ap);
    fflush(stdout);
    return ret;
}