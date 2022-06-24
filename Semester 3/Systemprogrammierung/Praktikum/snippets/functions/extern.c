/*
 * extern.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall extern.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int a = 1;

void f();

int main() {
    extern int a;   // Deklaration kann hier auch weggelassen werden, da a vorher definiert wurde
//    extern int a = 10;  // ???
//    int a;              // ???
    extern int b;   // muss deklariert werden

    a = 99;
    b = 42;

    printf("main()\n");
    printf("a: %d\n", a);
    printf("b: %d\n", b);

    f();
    f();

    return EXIT_SUCCESS;
}

int b;

void f() {
    b = 25;
    a++;

    printf("\nf()\n");
    printf("a: %d\n", a);
    printf("b: %d\n", b);
}
