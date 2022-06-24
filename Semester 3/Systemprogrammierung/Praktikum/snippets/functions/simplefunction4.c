/*
 * simplefunction4.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall simplefunction4.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Vorwaertsdeklaration */
int foo(int x);
// int foo(int x);

int main() {
    int x = foo(-1);
    printf("Rückgabe: %d\n", x);

    return EXIT_SUCCESS;
}

int foo(int x) {
    printf("Parameter: %d\n", x);
    return 42;
}

/*
int foo(int x) {
    printf("Parameter: %d\n", x);
    return 42;
}
*/

/*
double foo(double x) {
    printf("Parameter: %f\n", x);
    return 42;
}
*/
