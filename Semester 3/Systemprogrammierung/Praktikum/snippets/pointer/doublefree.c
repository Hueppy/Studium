/*
 * doublefree.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall doublefree.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *i, *k;
    i = (int *) malloc(sizeof(*i));
    k = i;

    free(i);

//    *i = 99; /* Speicher ist bereits frei */

//    free(i); /* EINMAL reicht! */

//    *k = 42; /* Speicher ist bereits frei - stale pointer */

//    free(k); /* Speicher ist bereits frei - double free */

    i = NULL;
    free(i);   /* free() auf NULL ist gefahrlos */

    return 0;
}
