/*
 * strcpy.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall strcpy.c`
 *
 */

#include <stdio.h>
#include <string.h>


char *strcpy1(char *s, const char *t);

char *strcpy2(char *s, const char *t);


int main() {
    char *str = "hallo welt";
    char buffer[100];    /* lang genug!!! */

    strcpy(buffer, "          ");
    printf("strcpy: '%s'\n", strcpy(buffer, str));

    strcpy(buffer, "          ");
    printf("strcpy1: '%s'\n", strcpy1(buffer, str));

    strcpy(buffer, "          ");
    printf("strcpy2: '%s'\n", strcpy2(buffer, str));


/*
    buffer[11] = 'a';
    buffer[12] = 'x';
*/
/*
    buffer[13] = '\0';
*/
    printf("manuell: '%s'\n", buffer);

    return 0;
}


char *strcpy1(char *s, const char *t) {
    int i = 0;

    while ((s[i] = t[i]) != '\0') {
        i++;
    }

    return s;
}


char *strcpy2(char *s, const char *t) {
    char *tmp = s;

    while (*s++ = *t++);

    return tmp;
}
