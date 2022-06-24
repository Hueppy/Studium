/*
 ============================================================================
 Name        : trC.c
 Author      : Carsten Gips
 Description : Taschenrechner in C, ANSI-Style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void opsEinlesen(int d, int *array) {
    int i;

    printf("\t%d Operanden eingeben\n", d);
    for (i = 0; i < d; i++) {
        scanf("%d", &array[i]);
    }
}

int main(void) {
    char buf[1024];
    int erg, i, d;
    int *ops;

    while (scanf("%s", buf)) {
        if (strcmp(buf, "print") == 0) {
            printf("\tErgebnis: %d\n", erg);

        } else if (strcmp(buf, "sum") == 0) {

            scanf("%d", &d);
            ops = (int *) malloc(d * sizeof(int));

            opsEinlesen(d, ops);

            erg = 0;
            for (i = 0; i < d; i++) {
                printf("\tZwischensumme: %d, Operand: %d, Index: %d\n", erg, ops[i], i);
                erg += ops[i];
            }

            free(ops);

        } else if (strcmp(buf, "end") == 0) {
            return EXIT_SUCCESS;

        } else {
            printf("Unbekannte Eingabe\n");
        }
    }

    return EXIT_SUCCESS;
}
