#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdarg.h>
void console_init(void);
int  console_printf(const char *fmt, ...);
#define LOG(...) console_printf(__VA_ARGS__)
#endif