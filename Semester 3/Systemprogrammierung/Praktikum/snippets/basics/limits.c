/*
 * limits.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall limits.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    printf("sizeof(unsigned char): \t'%lu'\n\n", sizeof(unsigned char));

    printf("sizeof(short int): \t'%lu'\n\n", sizeof(short int));

    printf("sizeof(int): \t\t'%lu'\n", sizeof(int));
    printf("sizeof(long int): \t'%lu'\n\n", sizeof(long int));

    printf("sizeof(float): \t\t'%lu'\n", sizeof(float));
    printf("sizeof(double): \t'%lu'\n", sizeof(double));
    printf("sizeof(long double): \t'%lu'\n", sizeof(long double));

    printf("\nINT_MAX: \t%d\n", INT_MAX);
    printf("INT_MIN: \t%d\n", INT_MIN);

    return EXIT_SUCCESS;
}
