#include "include/stdio.h"
#include "include/algorithm.h"
#include "include/string.h"
#include "include/tty.h"
#include "include/math.h"

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
	if(val_int == 0) terminal_putchar('0');
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
	free(buffer);
}

void printf(const char* format, ...) {
	va_list args;
	va_start(args, format);
	for(const char* symbol = format; *symbol != '\0'; symbol++) {
		if(*symbol == '%') {
			++symbol;
			switch(*(symbol))
			{
				case('c'): {
					int c = va_arg(args, int);
					terminal_putchar(c);
					break;
					}

				case('s'): {
					const char* s = va_arg(args, char*);
					while(*s) {
						terminal_putchar(*s++);
					}
                    			break;
					}

                		case('d'): {
                    			int d = va_arg(args, int);
					
					if(d < 0) {
						terminal_putchar('-');
						d = -d;
					}

					int dec = 1;
					while(d / dec > 9) {
						dec *= 10;
					}
					while(dec) {
						terminal_putchar((d / dec % 10) + '0');
						dec /= 10;
					}
                    			break;
					}

                		case('f'): {
					float f = (float)va_arg(args, double);
					float_to_char(f);
                    			break;
					}

                		case('p'): {
					uint16_t* p = va_arg(args, uint16_t*);
                    			printf("%d", p);
                    			break;
					}
			}
		}
		else {
			terminal_putchar(*symbol);
		}
		++symbol;
	}
	va_end(args);
}
