/*
 * bool.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall bool.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i = 0;

    if (-1) {
        printf("-1 wird als WAHR interpretiert\n");
    } else {
        printf("-1 wird als FALSCH interpretiert\n");
    }

    if (0) {
        printf("0 wird als WAHR interpretiert\n");
    } else {
        printf("0 wird als FALSCH interpretiert\n");
    }

    if (1) {
        printf("+1 wird als WAHR interpretiert\n");
    } else {
        printf("+1 wird als FALSCH interpretiert\n");
    }

    /* VORSICHT */
    printf("\n'i' hat den Wert '%d'\n", i);
    if (i = 3) {
        printf("ACHTUNG: 'i' hat jetzt den Wert '%d'\n", i);
    }
    printf("'i' hat den Wert '%d'\n", i);

    return EXIT_SUCCESS;
}
