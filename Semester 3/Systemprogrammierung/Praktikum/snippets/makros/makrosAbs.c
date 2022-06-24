/*
 * makrosAbs.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall makrosAbs.c`
 *
 */


#include <stdio.h>


#define  myAbs(x)  ((x)>=0 ? (x) : -(x))


int main() {
    int a = 9, y;

    y = myAbs (a);
    printf("y=%d\n\n", y);

    y = myAbs  (++a);
    printf("y=%d\n", y);
    printf("a=%d\n\n", a);

    y = myAbs  (a++);
    printf("y=%d\n", y);
    printf("a=%d\n", a);


    return 0;
}
