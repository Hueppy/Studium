/*
 * arrayZweiDim.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall arrayZweiDim.c`
 *
 */

#include <stdio.h>


void printTabelle2D(char tabelle[][7], size_t n, size_t m) {
// void printTabelle2D(char (*tabelle)[7], size_t n, size_t m) {
// void printTabelle2D(char **tabelle, size_t n, size_t m) {   /* FALSCH!!! */
    int i, j;

    printf("printTabelle2D: n: %ld, m: %ld, sizeof(tabelle): %ld, sizeof(tabelle[0]): %ld\n\n}", n, m, sizeof(tabelle),
           sizeof(tabelle[0]));

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("printTabelle2D: i: %d, j: %d => '%c'\n", i, j, tabelle[i][j]);
        }
    }
}


int main() {
    char o[][7] = {{'a', 'b', 'c', 'd', 'e', 'f', 'g'},
                   {'t', 'u', 'v', 'w', 'x', 'y', 'z'}};

    printf("\nMAIN: sizeof(tabelle): %ld, sizeof(tabelle[0]): %ld\n\n", sizeof(o), sizeof(o[0]));
    printTabelle2D(o, 2, 7);

    return 0;
}
