/*
 * simplefunction2.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall simplefunction2.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = foo(-1);
    printf("Rückgabe: %d\n", x);

    return EXIT_SUCCESS;
}

int foo(int x) {
    printf("Parameter: %d\n", x);
    return 42;
}
