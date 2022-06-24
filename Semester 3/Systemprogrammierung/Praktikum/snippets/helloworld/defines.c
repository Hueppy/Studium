/*
 * defines.c
 *
 * Author: Carsten Gips
 *
 * `gcc -E defines.c`
 *
 */

/* holt stdio.h aus Standardverzeichnis */

#include <stdio.h>
#include <stdlib.h>

/* Konstante MYMAX mit dem Wert 10 */
#define MYMAX 10

int main() {
    printf("Hello World from C  :-)\n");
    printf("mymax: 'MYMAX'\n");
    printf("mymax: '%d'\n", MYMAX);

    return EXIT_SUCCESS;
}
