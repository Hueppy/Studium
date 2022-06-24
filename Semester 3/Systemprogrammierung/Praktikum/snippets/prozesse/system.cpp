/*
 * system.cpp
 *
 * Author: Carsten Gips
 */


#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("Vor dem system()-Aufruf\n\n\n");
    system("/bin/ls -l /usr/bin");
    printf("\n\n\nNach dem system()-Aufruf\n");

    return EXIT_SUCCESS;
}
