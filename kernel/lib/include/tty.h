#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

extern bool list[25];

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_writestring(const char* data);
void terminal_write(const char* data, size_t size);
void terminal_putchar(char c);
void terminal_descent();
void remove_char(size_t value_column, size_t value_row);

#endif /* TERMINAL_H */
