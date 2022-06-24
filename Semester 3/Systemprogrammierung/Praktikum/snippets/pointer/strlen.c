/*
 * strlen.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall strlen.c`
 *
 */

#include <stdio.h>
#include <string.h>


int strlen1(const char *s);

int strlen2(const char *s);


int main() {
    char *str = "hallo welt";
    /* char str[] = "hallo welt"; */

    printf("strlen: %ld\n", strlen(str));
    printf("strlen1: %d\n", strlen1(str));
    printf("strlen2: %d\n", strlen2(str));

    return 0;
}


int strlen1(const char *s) {
    const char *p = s;
    int length = 0;

    while (*p) {
        length++;
        p++;
    }

    return length;
}


int strlen2(const char *s) {
    const char *p = s;

    while (*p++);

    return p - s - 1;
}
