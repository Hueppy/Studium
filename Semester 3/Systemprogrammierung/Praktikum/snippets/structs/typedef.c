/*
 * typedef.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall typedef.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

    typedef struct point {
        int x;
        int y;
    } Point;

    Point a;
    struct point b;
    Point c = {9, 7};       // Initialisierungsliste
    Point d = {.x=9, .y=7}; // ab C99: "designated initializers"

    a.x = 10;
    a.y = 10;

    b.x = 42;
    b.y = 1;

    printf("Punkt a: x=%d, y=%d\n", a.x, a.y);
    printf("Punkt b: x=%d, y=%d\n", b.x, b.y);
    printf("Punkt c: x=%d, y=%d\n", c.x, c.y);
    printf("Punkt d: x=%d, y=%d\n", d.x, d.y);

    return EXIT_SUCCESS;
}
