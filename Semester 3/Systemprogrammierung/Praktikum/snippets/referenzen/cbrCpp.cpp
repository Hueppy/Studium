/*
 * cbrCpp.c
 *
 * Author: Carsten Gips
 */

#include <cstdio>
#include <cstdlib>

int add_5(int &);

int main() {
    int i = 0, erg;
    printf("i vorher: %d\n\n", i);

    erg = add_5(i);
    printf("i nachher: %d\n", i);
    printf("erg: %d\n", erg);

    return EXIT_SUCCESS;
}

int add_5(int &x) {
    x += 5;
    return x;
}
