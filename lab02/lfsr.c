#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

#include "bit_ops.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    int t = *reg;
    int n = t & 1;
    t = (*reg >> 2) & 1;
    n ^= t;
    t = (*reg >> 3) & 1;
    n ^= t;
    t = (*reg >> 5) & 1;
    n ^= t;

    *reg = *reg >> 1;
    t = (*reg >> 15) & 1;
    n ^= t;
    n <<= 15;
    *reg ^= n;
}
