/*
 * cbv.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall cbv.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int add_5(int);

int main() {
    int erg, i = 0;
    printf("i: %d\n", i);

    erg = add_5(i);
    printf("\nerg: %d\n", erg);
    printf("i: %d\n", i);

    return EXIT_SUCCESS;
}

int add_5(int x) {
    x += 5;
    return x;
}
