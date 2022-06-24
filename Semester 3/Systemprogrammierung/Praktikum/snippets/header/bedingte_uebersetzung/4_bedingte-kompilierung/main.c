/*
 * main.c
 *
 * Author: Carsten Gips
 *
 * `gcc -c main.c;  gcc -c blatt.c;  gcc main.o blatt.o`
 *
 */

#include "blatt.h"
#include "struct.h"

int main() {
    fkt1();
    fkt2();

    struct studi s = {"Holger", 7};
    wuppie(s);
}
