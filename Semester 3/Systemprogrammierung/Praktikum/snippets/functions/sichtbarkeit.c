/*
 * sichtbarkeit.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall sichtbarkeit.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int a = 1, b = 2;

int main() {
    extern int a;
    int b = 3;

    a = 99;

    printf("main()\n");
    printf("a: %d\n", a);
    printf("b: %d\n", b);

    {
        int b = 20;
        int c = 300;

        printf("\nmain(), innerer Block\n");
        printf("b: %d\n", b);
        printf("c: %d\n", c);
    }

    printf("\nmain(), nach innerem Block\n");
    printf("a: %d\n", a);
    printf("b: %d\n", b);
    printf("c: %d\n", c);

    return EXIT_SUCCESS;
}
