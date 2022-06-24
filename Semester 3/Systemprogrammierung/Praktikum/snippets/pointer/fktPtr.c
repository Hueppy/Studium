/*
 * fktPtr.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall fktPtr.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>


int cmp(int a, int b, int (*krit)(int, int)) {
    return (*krit)(a, b);  /* alternativ auch: return krit(a, b); */
}


int kleiner(int a, int b) {
    printf("\nFunktion kleiner\n");
    printf("\tArgument a: %d\n", a);
    printf("\tArgument b: %d\n", b);

    return a < b;
}

int gleich(int a, int b) {
    printf("\nFunktion gleich\n");
    printf("\tArgument a: %d\n", a);
    printf("\tArgument b: %d\n", b);

    return a == b;
}


int main() {
    int (*fp)(int, int) = &kleiner;
    /* alternativ auch: ... = kleiner; */

    printf("main: a<b: %d\n", cmp(1, 2, fp));
    printf("main: a==b: %d\n", cmp(1, 2, gleich));

    return EXIT_SUCCESS;
}
