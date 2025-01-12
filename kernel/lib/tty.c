#include "include/tty.h"
#include "include/vga.h"
#include "include/string.h"
#include "include/io.h"
#include <stddef.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

void move_cursor(uint16_t x, uint16_t y) {
    uint16_t position = y * VGA_WIDTH + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}


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

static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void remove_char(size_t value_column, size_t value_row) {
    for(size_t i = value_column; i < VGA_WIDTH; i++) terminal_putentryat(' ', terminal_color, i, value_row);
    move_cursor(terminal_column, terminal_row);
}

void terminal_descent() {
    char s;
    for(size_t i = 0; i < VGA_HEIGHT; i++) {
        for(size_t j = 0; j <= VGA_WIDTH; j++) {
            s = terminal_buffer[(i + 1) * VGA_WIDTH + j];
            terminal_putentryat(s, terminal_color, j, i);
        }
    }
}

void terminal_putchar(char c) 
{
    if (c == '\n') {
        c = ' ';
        terminal_putentryat(c, terminal_color, terminal_column++, terminal_row);
        if (++terminal_row >= VGA_HEIGHT) {
            remove_char(terminal_column, VGA_HEIGHT);
            terminal_descent();
            terminal_row = VGA_HEIGHT - 1;
        }
        terminal_column = 0;
        move_cursor(terminal_column, terminal_row);
        return;
    }
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column >= VGA_WIDTH) {
        if (++terminal_row >= VGA_HEIGHT) {
            terminal_row = VGA_HEIGHT - 1;
            terminal_descent();
        }
        terminal_column = 0;
    }

    move_cursor(terminal_column, terminal_row);
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
