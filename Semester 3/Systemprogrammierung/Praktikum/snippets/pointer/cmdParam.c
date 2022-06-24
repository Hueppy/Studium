/*
 * cmdParam.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall cmdParam.c`
 *
 */

#include <stdio.h>


int main(int argc, char *argv[]) {
// int main(int argc, char **argv) {
// int main(int argc, char argv[][]) {  /* FALSCH */
    /*
    *  argc: Anzahl der Argumente+1
    *  argv: Array von Pointern auf char
    *  argv[0]: Name des Programms
    *  argv[1] bis argv[argc-1]: Argumente ('\0'-terminiert)
    *  argv[argc]: 0 (Nullpointer)
    */
    int i;

    for (i = 0; i <= argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}
