/*
 * strEinlesen.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall strEinlesen.c`
 *
 */

#include <stdio.h>
#include <string.h>


void f1(void);

void f2(void);

void f3(void);

void f4(void);


int main() {
    f4();

    return 0;
}


void f1(void) {
    char *x;
    scanf("%s", x); /* AUTSCH */
}


void f2(void) {
    char *x = "12345";
    scanf("%s", x); /* AUTSCH */
}


void f3(void) {
    char buffer[5];
    scanf("%s", buffer);  /* OK, falls weniger als 5 Zeichen eingelesen */
    printf("gelesen: '%s'\n", buffer);
}


void f4(void) {
    char zeile[10];
    fgets(zeile, 10, stdin);  /* liest maximal 9 Zeichen */
    printf("gelesen: '%s'\n", zeile);
}
