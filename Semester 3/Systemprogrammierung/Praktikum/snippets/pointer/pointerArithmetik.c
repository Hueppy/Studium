/*
 * pointerArithmetik.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall pointerArithmetik.c`
 *
 */

#include <stdio.h>


int main() {
    double d[10];
    double *d1 = &d[2];
    double *d2 = d1;

    d2++;

    printf("d2-d1:               %ld\n", d2 - d1);                  /* ergibt 1 */
    printf("(long)d2 - (long)d1: %ld\n", (long) d2 - (long) d1);    /* ergibt 8 (falls double 8 Byte sind) */

    printf("\n");
    printf("sizeof(d1):  %ld\n", sizeof(d1));     /* Breite der Pointervariablen: 4 Bytes */
    printf("sizeof(*d1): %ld\n", sizeof(*d1));    /* Breite des Pointerdatentyps: double = 8 Byte */

    return 0;
}
