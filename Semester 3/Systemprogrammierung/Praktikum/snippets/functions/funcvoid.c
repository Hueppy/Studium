/*
 * funcvoid.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall funcvoid.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>


int f1(void);
int f2();
int f3();


int main() {
    /* legaler Gebrauch */
    f1();
    f2();
    f3(42);

    /* falscher Gebrauch */
    f1(42);     /* Compiler: Fehler: too many arguments to function ‘f1’ */
    f2(42);     /* LEGAL! (42 ist in f2 nicht sichtbar)                  */
    f3(42, 43); /* LEGAL! (nur 42 ist in f3 sichtbar)                    */

    return EXIT_SUCCESS;
}


int f1(void) {
    printf("Huhu von f1\n");
    return 0;
}

int f2() {
    printf("Huhu von f2\n");
    return 0;
}

int f3(int a) {
    printf("Huhu von f3: a=%d\n", a);
    return 0;
}


// Legal in C
// Deklaration: "Ich verrate Dir nicht, wieviele Parameter wuppie() hat."
int wuppie();
int wuppie(int x) { return x; }


// Fehler in C
// Deklaration: fluppie() hat KEINE Parameter!
int fluppie(void);
int fluppie(int x) { return x; }
