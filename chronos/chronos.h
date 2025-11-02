#include "scheduler.h"
#include <console.h>

#define LOG_INIT(x)     console_init(x)
#define LOG(...)        console_printf(__VA_ARGS__)