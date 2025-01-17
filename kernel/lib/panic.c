#include <stdarg.h>
#include "include/stdio.h"
#include "include/panic.h"

_Noreturn void panic(const char* fmt, ...)
{
    printf("Kernel panic: %s", fmt);

    __asm__ volatile ("cli");
    while (1) 
    {
        __asm__ volatile ("hlt");
    }
}
