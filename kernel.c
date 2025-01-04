#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;	//(00000111 | (00000000 << 4)) = 00000111
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8; //(0000000000000000 | (0000000000000111 << 8)) = 00000111 00000000
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
    if (c == '\n') {
		c = ' ';
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row++);
        terminal_column = 0;
        return;
    }
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row >= VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

//реализация функций для printf

void insert(char* buff, int index_point, int size, char sym) {
    for(int i = size; i > index_point; i--) {
        buff[i] = buff[i - 1];
    }
    buff[index_point] = sym;
}

float round(float a, int b) {

}

void reverse(char* start, char* end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void int_to_char(int val) {
    char* buffer;
    int i = 0;
    if(val < 0) {
        val = -val;
        terminal_putchar('-');
    }
    while(val > 0) {
        buffer[i++] = (val % 10) + 0x30;
		val /= 10;
    }
    reverse(buffer, buffer + i - 1);
    buffer[i] = '\0';
    terminal_write(buffer, i);
}

void float_to_char(float val) {
	char* buffer;
	if(val < 0) {
        val = -val;
        terminal_putchar('-');
    }
	int val_int = val;
	int val_float = val * 1000; // точность тысячные
	int i = 0;
    int index_point = 0;
    while(val_float > 0) {
        if(val_int > 0) {
            index_point++;
            val_int /= 10;
        }
        buffer[i++] = (val_float % 10) + 0x30;
        val_float /= 10; 
    }
	reverse(buffer, buffer + i - 1);
    insert(buffer, index_point, i, '.');
	buffer[i + index_point] = '\n';
	terminal_write(buffer, i + index_point);
}


void printff(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char c;
    const char* s;
	int d;
	float f;
    for(const char* symbol = format; *symbol != '\0'; symbol++) {
		if(*symbol == '%') {
			switch(*(symbol + 1))
			{
				case('c'):
					c = (char)va_arg(args, int);
                    terminal_putchar(c);
                    symbol++;
                    break;
                case('s'):
                    s = va_arg(args, const char*);
                    terminal_write(s, strlen(s));
                    symbol++;
                    break;
                case('d'):
                    d = va_arg(args, int);
                    int_to_char(d);
                    symbol++;
                    break;
                case('f'):
					f = (float)va_arg(args, double);
					float_to_char(f);
					symbol++;
                    break;
			}
		}
		else terminal_putchar(*symbol);
	}
	terminal_putchar('\n');
    va_end(args);
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	char s = '1';
	const char* str = "Hm... it is";
	int a = -2134;
	float f = 1134.129123; // на 7-9 уходит одна десятая

	/* Newline support is left as an exercise. */
	printff("  _____              ____   _____\n / ____|            / __ \\ / ____|\n| |  __  __ _ _   _| |  | | (___  \n| | |_ |/ _` | | | | |  | |\\___ \\ \n| |__| | (_| | |_| | |__| |____) |\n \\_____|\\__,_|\\__, |\\____/|_____/\n               __/ |              \n              |___/               \n");
	printff("Hello world %c OMG!!!! %s AHAHAHAHAH", s, str);
	printff("GOOD JOB %d", a);
	printff("mmmmmmmm. New float? %f", f);
}