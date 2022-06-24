/*
 * simpleArrays.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall simpleArrays.c`
 *
 */

#define MAX 100

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;

    double x[] = {12.2, 45.4, 67.2, 12.2};    // Array mit 4 Eintraegen
    int y[MAX];                               // Array mit MAX Eintraegen
    double z[10] = {12.2};    // Array mit 10 Eintraegen (alle initialisiert!)

/*
    double x1[];
    x1=x;   // VERBOTEN
*/

    /* Initialisierung */
    printf("x[0]: %f\n", x[0]);
    printf("y[0]: %d\n\n", y[0]);
    printf("z[0]: %f\nz[1]: %f\n\n", z[0], z[1]);

    for (i = 0; i < MAX; i++) {
        y[i] = 0;
    }

    /* Anzahl der Elemente */
    printf("sizeof(x)/sizeof(x[0]): %lu\n", sizeof(x) / sizeof(x[0]));
    printf("sizeof(x):              %lu\n\n", sizeof(x));

    /* Vorsicht Indexbereich */
    y[MAX] = 99;

    return EXIT_SUCCESS;
}
