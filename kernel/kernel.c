#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lib/include/vga.h"
#include "lib/include/tty.h"
#include "lib/include/string.h"
#include "lib/tty.c"
#include "lib/string.c"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	terminal_initialize();

	terminal_writestring("  _____              ____   _____\n / ____|            / __ \\ / ____|\n| |  __  __ _ _   _| |  | | (___  \n| | |_ |/ _` | | | | |  | |\\___ \\ \n| |__| | (_| | |_| | |__| |____) |\n \\_____|\\__,_|\\__, |\\____/|_____/\n               __/ |              \n              |___/               \n");
}
