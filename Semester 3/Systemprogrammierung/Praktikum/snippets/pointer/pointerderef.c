/*
 * pointerderef.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall pointerderef.c`
 *
 */

#include <stdio.h>

int main() {

    int i = 99;
    int *iptr;

    iptr = &i;

    printf("\nVorher\n");
    printf("Wert von i: %d\n", i);
    printf("Adresse von i: %p\n\n", &i);
    printf("Wert von iptr: %p\n", iptr);
    printf("Adresse von iptr: %p\n", &iptr);
    printf("iptr dereferenziert: %d\n\n\n", *iptr);

    *iptr = 2;

    printf("\nNachher\n");
    printf("Wert von i: %d\n", i);
    printf("Adresse von i: %p\n\n", &i);
    printf("Wert von iptr: %p\n", iptr);
    printf("Adresse von iptr: %p\n", &iptr);
    printf("iptr dereferenziert: %d\n", *iptr);

    return 0;
}
