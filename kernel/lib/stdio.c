#include "include/stdio.h"
#include "include/algorithm.h"
#include "include/string.h"
#include "include/tty.h"
#include "include/math.h"

void int_to_char(int val) {
    char* buffer = (char*)calloc(12, sizeof(char));
    int i = 0;
    if(val == 0) {
        terminal_putchar('0');
        return;
    }
    if(val < 0) {
        val = -val;
        terminal_putchar('-');
    }
    while(val > 0) {
        buffer[i++] = (val % 10) + 0x30;
		val /= 10;
    }
    reverse(buffer, buffer + i - 1);
    terminal_write(buffer, i);
}

void float_to_char(float val) {
    char* buffer = (char*)calloc(33, sizeof(char));
    if(val < 0) {
        val = -val;
        terminal_putchar('-');
    }
    long long val_int = val;
    float val_float = val - val_int;
    size_t count_factional = 0;
    if(val_float > 0.5) val_float -= 0.5f;
    while(val_float < 1 || count_factional > 23) {
        val_float *= 2;
        count_factional++;
    }
    size_t index_point = 0;
     while(val_int > 0) {
        index_point++;
        val_int /= 10;
    }
    val_int = val * pow(10, count_factional);
    size_t i = 0;
    while(val_int > 0) {
        buffer[i++] = (val_int % 10) + 0x30;
        val_int /= 10;
    }
    reverse(buffer, buffer + i - 1);
    insert(buffer, index_point, i + 1, '.');
    terminal_write(buffer, i + 1);
}

void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char c;
    const char* s;
	int d;
	float f;
    uint16_t* p;
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
                case('p'):
					p = va_arg(args, uint16_t*);
                    printf("%d", p);
					symbol++;
                    break;
			}
		}
		else {
            terminal_putchar(*symbol);
        }
	}
    va_end(args);
}
