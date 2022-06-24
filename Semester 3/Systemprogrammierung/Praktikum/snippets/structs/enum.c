/*
 * enum.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall enum.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;

    enum Wochentag {
        SONNTAG, MONTAG = 3, DIENSTAG, MITTWOCH
    } tag;
    enum Wochentag feier_tag = SONNTAG;

    tag = MONTAG;
    tag += 1;
    x = tag + feier_tag;

    printf("tag: %d\n", tag);
    printf("feier_tag: %d\n", feier_tag);
    printf("MITTWOCH: %d\n", MITTWOCH);
    printf("x: %d\n", x);

    return EXIT_SUCCESS;
}
