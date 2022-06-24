/*
 * bitop.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall bitop.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned char x;

    x = 5;      /*    0000 0101 */
    x = x & 3;  /* 3: 0000 0011; AND: 0000 0001: 1 */
    printf("x: %d\n", x);

    x = 5;      /*    0000 0101 */
    x = x | 3;  /* 3: 0000 0011; OR: 0000 0111: 7 */
    printf("x: %d\n", x);

    x = 5;      /* 0000 0101 */
    x = x << 2; /* 0001 0100: 20 */
    printf("x: %d\n", x);

    return EXIT_SUCCESS;
}
