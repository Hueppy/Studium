/*
 * arrayDyn.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall arrayDyn.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>


void printTabelle2D(int **tabelle, size_t n, size_t m) {
// void printTabelle2D(int (*tabelle)[6], size_t n, size_t m) {  /* FALSCH!!! */
    int i, j;

    printf("n: %ld, m: %ld, sizeof(tabelle): %ld\n", n, m, sizeof(tabelle));
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("i: %d, j: %d => %d\n", i, j, tabelle[i][j]);
        }
    }
}

int main() {
    size_t r = 2, c = 6;
    int i, j;

    /* Matrix anlegen */
    int **p2 = (int **) malloc(r * sizeof(int *));
    for (i = 0; i < r; i++) {
        p2[i] = (int *) malloc(c * sizeof(int));
    }


    /* Matrix nutzen */
    p2[0][0] = 0;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            p2[i][j] = i + j;
        }
    }
    printTabelle2D(p2, r, c);


    /* Matrix freigeben */
    for (i = 0; i < r; i++) {
        free(p2[i]);
    }
    free(p2);

    return 0;
}
