#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "lib/include/vga.h"
#include "lib/include/string.h"
#include "lib/include/stdio.h"
#include "lib/include/kbd.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

__attribute__((noinline)) void test(void)
{
    // volatile char buf[8];
    // for (int i = 0; i < 7; i++)
    //     buf[i] = 'A';

    // for (int i = 0; i < 7; i++) {
	// 	printf("%d ", buf[i]);
    // }

	// int *top = 0xB00;
	// printf("%p\n", top);
}



void kernel_main(void) 
{

	terminal_initialize();

	test();

	printf("  _____              ____   _____\n / ____|            / __ \\ / ____|\n| |  __  __ _ _   _| |  | | (___  \n| | |_ |/ _` | | | | |  | |\\___ \\ \n| |__| | (_| | |_| | |__| |____) |\n \\_____|\\__,_|\\__, |\\____/|_____/\n               __/ |              \n              |___/               \n");

	while(1)
	{
		keyboard_interrupt_handler();
	}
}
