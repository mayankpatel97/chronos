#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdarg.h>

void console_init(void);

int console_putc(char c);

int console_puts(const char *s);

int console_print(const char *fmt, ...);

#endif