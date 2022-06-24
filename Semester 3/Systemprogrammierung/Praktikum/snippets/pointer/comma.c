/*
 * comma.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall comma.c`
 *
 */

#include <stdio.h>


int main() {
    int i, j;

    for (i = 10, j = i; i >= 0, j >= 0; i--, j--) {
        printf("i: %d, j: %d\n", i, j);
    }

    return 0;
}
