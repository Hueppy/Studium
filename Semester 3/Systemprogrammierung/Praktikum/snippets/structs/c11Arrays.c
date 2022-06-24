/*
 * c11Arrays.c
 *
 * Author: Carsten Gips
 *
 * `gcc --std=c11 -pedantic c11Arrays.c`
 *
 */


#include <stdio.h>
#include <stdlib.h>

int main() {
    int cnt;

    printf("Bitte ganze Zahl eingeben:\n");
    scanf("%d", &cnt);  // sorry, Vorgriff auf VL04 :-)

    int x[cnt]; // Array mit variabler Laenge, seit C11

    printf("sizeof(x)/sizeof(x[0]): %lu\n", sizeof(x) / sizeof(x[0]));


    return EXIT_SUCCESS;
}
