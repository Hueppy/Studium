/*
 * arrayEinDim.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall arrayEinDim.c`
 *
 */

#include <stdio.h>


void printTabelle1D(char tabelle[], int n) {
// void printTabelle1D(char tabelle[7], int n) {
// void printTabelle1D(char *tabelle, int n) {
    int i;

    printf("printTabelle1D: n: %d, sizeof(tabelle): %ld\n\n", n, sizeof(tabelle));

    for (i = 0; i < n; i++) {
        printf("printTabelle1D: i: %d => '%c'\n", i, tabelle[i]);
    }
}


int main() {
    char o[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    printf("\nMAIN: sizeof(tabelle): %ld\n\n", sizeof(o));
    printTabelle1D(o, 7);

    return 0;
}
