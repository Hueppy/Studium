/*
 * simplefunction.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall simplefunction.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int x) {
    printf("Parameter: %d\n", x);
    return 42;
}

int main() {
    int x = foo(-1);
    printf("Rückgabe: %d\n", x);

    return EXIT_SUCCESS;
}
