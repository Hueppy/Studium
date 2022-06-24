/*
 * structs.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall structs.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

    struct point {
        int x;
        int y;
    } a;

    struct point b;

    a.x = 10;
    a.y = 10;

    b.x = 42;
    b.y = 1;

    printf("Punkt a: x=%d, y=%d\n", a.x, a.y);
    printf("Punkt b: x=%d, y=%d\n", b.x, b.y);

    return EXIT_SUCCESS;
}
