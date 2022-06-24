/*
 * blatt.c
 *
 * Author: Carsten Gips
 *
 * `gcc -c main.c;  gcc -c blatt.c;  gcc main.o blatt.o`
 *
 */

#include "blatt.h"
#include "struct.h"

void fkt2() {
    42;
}

void fkt1() {
    fkt2();
}

int wuppie(struct studi s) {
    return s.credits;
}
