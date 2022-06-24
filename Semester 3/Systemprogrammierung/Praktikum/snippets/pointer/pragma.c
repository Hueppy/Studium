/*
 * pragma.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall pragma.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>


#pragma GCC poison printf sprintf fprintf

// ab C99 auch als Operator `_Pragma()`
//_Pragma("GCC poison printf sprintf fprintf")



int main() {
    printf("Hello World :-)\n");

    return EXIT_SUCCESS;
}
