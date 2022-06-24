/*
 * blatt.c
 *
 * Author: Carsten Gips
 *
 * `gcc -c main.c;  gcc -c blatt.c;  gcc main.o blatt.o`
 *
 */

#include "blatt.h"

void fkt2() {
    42;
}

void fkt1() {
    fkt2();
}
