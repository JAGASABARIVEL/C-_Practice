#include "iostream"
#include "mymath.h"

using namespace std


int pow(int base, int exponent) {
    int total = 1;
    for (int i = 0; i < exponent; i++) {
        total = total * base;
    }
    return total;
}