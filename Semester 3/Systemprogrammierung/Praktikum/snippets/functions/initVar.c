/*
 * initVar.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall initVar.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

void a();

void b();

void c();

int x;
int y = 1;

int main() {
    int x = 5;
    int z;

    printf("main(): x=%d (lokal, manuell initialisiert)\n", x);
    printf("main(): z=%d (lokal, nicht initialisiert)\n\n", z);
    {
        extern int x;
        printf("main(): x=%d (global, nicht initialisiert)\n", x);
        printf("main(): y=%d (global, manuell initialisiert)\n\n", y);
    }

    a();
    b();
    c();
    a();
    b();
    c();
    a();
    b();
    c();

    return EXIT_SUCCESS;
}

void a() {
    int x = 25;
    x++;
    printf("a(): x=%d\n", x);
}

void b() {
    static int x;
    x++;
    printf("b(): x=%d\n", x);
}

void c() {
    x++;
    printf("c(): x=%d\n", x);
}
