/*
 * c_bin_streams.c
 *
 * Author: Carsten Gips
 */

#include <stdio.h>
#include <stdlib.h>

#define PANIC(msg)  {perror(msg); abort();}

int main(int argc, char *argv[]) {
    FILE *f;

    /* Struktur */
    struct studi {
        char name[100];
        unsigned int credits;
    } s, heinz = {"Heinz", 10};


    /* Struktur schreiben */
    f = fopen("data", "wb");
    if (!f) {
        PANIC("fopen wb");
    }

    if (!fwrite(&heinz, sizeof(struct studi), 1, f)) {
        PANIC("fwrite");
    }

    if (fclose(f) != 0) {
        PANIC("fclose");
    }


    /* Struktur lesen */
    f = fopen("data", "rb");
    if (!f) {
        PANIC("fopen rb");
    }

    if (!fread(&s, sizeof(struct studi), 1, f)) {
        PANIC("fread");
    }

    if (fclose(f) != 0) {
        PANIC("fclose");
    }

    printf("Studi gelesen: name=%s, credits=%d\n", s.name, s.credits);


    return 0;
}
