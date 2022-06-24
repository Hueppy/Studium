/*
 * generic.c
 *
 * Author: Carsten Gips
 *
 * `gcc -std=c11 -Wall generic.c`
 *
 */


#include <stdio.h>
#include <stdlib.h>


void bar(int x) {
    printf("bar: x=%d\n", x);
}

void bar_f(float x) {
    printf("bar_f: x=%.2f\n", x);
}

void bar_d(double x) {
    printf("bar_d: x=%.6f\n", x);
}

void bar_c(char x) {
    printf("bar_c: x=%c\n", x);
}


#define foo(X) _Generic( (X),               \
                         float: bar_f,      \
                         double: bar_d,     \
                         char: bar_c,       \
                         default: bar       \
                         )(X)


#define type_idx(T) _Generic( (T),          \
                              int: 1,       \
                              long: 2,      \
                              float: 3,     \
                              default: 0)


int main(void) {
    int i = 4;
    float f = 1.2f;
    double d = 3.2;
    char c = 'A';

    printf("type_idx(i): %d\n", type_idx(i));
    printf("type_idx(f): %d\n", type_idx(f));
    printf("type_idx(d): %d\n", type_idx(d));
    printf("type_idx(c): %d\n\n", type_idx(c));


    foo(i);     // Defaultwert (int)
    foo(f);     // float
    foo(d);     // double
    foo(c);     // char
}
