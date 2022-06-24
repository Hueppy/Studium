/*
 * cstrings.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall cstrings.c`
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    /* C-Strings sind Char-Arrays */
    char str[] = "Dies ist ein Text";
    printf("str: %s\n", str);
    str[4] = 'O';
    printf("str: %s\n\n", str);

    /* Strings haben als letztes Zeichen eine "\0" */
    char a[] = "0123456789";
    char b[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    printf("a[3]: %c\n", a[3]);
    printf("b[3]: %c\n", b[3]);

    printf("a: %s\n", a);
    printf("b: %s\n", b);

    printf("laenge a: %ld\n", sizeof(a) / sizeof(a[0]));
    printf("laenge b: %ld\n", sizeof(b) / sizeof(b[0]));

    /* char-Array fuellen */
    char c[100];
    strcpy(c, "hello world :)");  /* man 3 strcpy */
    printf("c: '%s'\n", c);
    strcpy(c, "wuppie");
    printf("c: '%s'\n", c);

    return EXIT_SUCCESS;
}
