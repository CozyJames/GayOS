#include "include/math.h"

double pow(double base, double exponent) {
    if (exponent == 0) {
        return 1;
    }

    double result = 1;
    for (int i = 0; i < (int)exponent; i++) {
        result *= base;
        if (result > 1000000) {
            result = 1000000;
            break;
        }
    }

    return result;
}