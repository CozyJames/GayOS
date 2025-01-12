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

void kernel_main(void) 
{
	terminal_initialize();

	char s = '1';
	const char* str = "Hm... it is";
	int a = -2134;
	float f = 1134.129123;
	printf("  _____              ____   _____\n / ____|            / __ \\ / ____|\n| |  __  __ _ _   _| |  | | (___  \n| | |_ |/ _` | | | | |  | |\\___ \\ \n| |__| | (_| | |_| | |__| |____) |\n \\_____|\\__,_|\\__, |\\____/|_____/\n               __/ |              \n              |___/               \n");
	printf("Hello world %c OMG!!!! %s AHAHAHAHAH\n", s, str);
	printf("GOOD JOB %d BAD JOB %f\n", a, f);

	char* username = "root";
	char* pc_name = "shitbox";
	while(1)
	{
		// printf("%s@%s:~$ ", username, pc_name);
		keyboard_interrupt_handler();
	}
}
