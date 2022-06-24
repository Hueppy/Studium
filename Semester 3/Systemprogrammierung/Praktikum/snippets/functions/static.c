/*
 * static.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall static.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

void foo() {
    static int x = 42;
    x++;
    printf("x=%d\n", x);
}

int main() {
    foo();
    foo();
    foo();

    return EXIT_SUCCESS;
}
