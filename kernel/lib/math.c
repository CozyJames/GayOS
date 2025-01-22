#include "include/math.h"

double pow(double value, double power) {
    if(power == 0) return 1;
    for(int i = 1; i < power; i++) value *= value;
    if(value > 1000000) value = 1000000;
    return value;
}