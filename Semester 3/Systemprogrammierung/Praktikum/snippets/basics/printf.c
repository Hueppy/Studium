/*
 * printf.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall printf.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf(":%d: :%s: :%s: :%.2f:\n", 42, "Hello", "World", 23.745);
    /*:42: :Hello: :World: :23.75:*/

    printf(":%-5d: :%-10s: :%-10s: :%10.2f:\n", 42, "Hello", "World", 23.745);
    /*:42   : :Hello     : :World     : :     23.75:*/
    /* 5 Zeichen inkl. "42" (linksbuendig)          */
    /* 10 Zeichen inkl. "Hello" (analog "World")    */
    /* 10 Zeichen inkl. 23.75 (rechtsbuendig)       */

    return EXIT_SUCCESS;
}
