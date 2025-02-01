#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "lib/include/vga.h"
#include "lib/include/string.h"
#include "lib/include/stdio.h"
#include "lib/include/kbd.h"
#include "lib/include/gdt.h"
#include "lib/include/panic.h"

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
const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;
bool list[25];

__attribute__((noinline)) void test(void)
{
    // volatile char buf[8];
    // for (int i = 0; i < 7; i++)
    //     buf[i] = 'A';

    // for (int i = 0; i < 7; i++) {
	// 	printf("%d ", buf[i]);
    // }

	// uintptr_t top = 0xB800;
	// printf("%p\n", top);
}



void kernel_main(void) 
{

	terminal_initialize(); 
    gdt_install();

    if (!gdt_verify()) {
        panic("GDT not installed as expected!\n");
        while (1) { __asm__ volatile("hlt"); }
    } else {
        printf("GDT installed successfully!\n");
    }

	printf("  _____              ____   _____\n / ____|            / __ \\ / ____|\n| |  __  __ _ _   _| |  | | (___  \n| | |_ |/ _` | | | | |  | |\\___ \\ \n| |__| | (_| | |_| | |__| |____) |\n \\_____|\\__,_|\\__, |\\____/|_____/\n               __/ |              \n              |___/               \n");

    printf("%s@%s:~$ ", username, pc_name);

	while (1) 
	{
        if(keyboard_interrupt_handler() == KEYBOARD_PRESS_ENTER)
		{
            printf("%s@%s:~$ ", username, pc_name);
        }
    }
}
