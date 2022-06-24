/*
 * fgets.c
 *
 * Author: Carsten Gips
 */

#include <stdio.h>
#include <stdlib.h>

#define PANIC(msg)  {perror(msg); abort();}
#define BUFSIZE 1024


char *my_fgets(char *str, int n, FILE *stream) {
    int c = 0;
    char *s = str;
    char d = ':';    // Delimiter (Original: `\n`), darf nicht '\0' sein!

    while (--n > 0 && (c = fgetc(stream)) != EOF && (*s++ = c) != d) { ;
    }

    if (c == d) {
        --s;
    }
    *s = '\0';

    return str;
}


int main(int argc, char *argv[]) {
    FILE *f;
    char buf[BUFSIZE];

    f = fopen("wochentage.txt", "r");
    if (!f) {
        PANIC("fopen w");
    }

    for (int i = 0; i < 12; i++) {
        my_fgets(buf, BUFSIZE, f);
        printf("gelesen: '%s'\n", buf);
    }

    if (fclose(f) != 0) {
        PANIC("fclose");
    }

    return EXIT_SUCCESS;
}
