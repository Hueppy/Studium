/*
 * makrosSymb.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall makrosSymb.c`
 *
 */


#include <stdio.h>


#define  printDebug(expr)  printf("%s [%d] %s: %d\n",  \
                                   __FILE__, __LINE__, \
                                   #expr, expr)


int main() {
    int a = 9, y = 42;


    printDebug(y);
    printDebug(a);
    printDebug(a + y);


    return 0;
}
