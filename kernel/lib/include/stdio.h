#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <stdint.h>

void int_to_char(int val);
void float_to_char(float val);
void printf(const char* format, ...);

#endif /* STDIO_H */