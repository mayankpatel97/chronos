#include <stdio.h>
#include "console.h"
#include "pal.h"

int main()
{
    console_init();
    console_print("Hello This is a test\n");
    while (1)
    {
        pal_delay_ms(500);
        console_print("print 1\n");
        pal_delay_ms(500);   
        console_print("print 2\n");
    }
}