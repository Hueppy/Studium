/*
 * nullptr.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall nullptr.c`
 * `gcc -Wall nullptr.c -DNDEBUG`
 *
 */


#include <stdio.h>
#include <stdlib.h>


#ifdef NDEBUG
#define DEBUG(m) printf("%s\n", m);
#else
#define DEBUG(m) ;
#endif  // NDEBUG

#define CHECK(p,m) if (p==NULL) {  \
    DEBUG(m)                       \
    exit(-1);                      \
}


int main() {
    int x = 42, *a = &x, *b = 0;

    printf("vor CHECK (a)\n");
    CHECK(a, "Null-Pointer: a!")
    printf("nach CHECK (a)\n\n");

    printf("vor CHECK (b)\n");
    CHECK(b, "Null-Pointer: b!")
    printf("nach CHECK (b)\n");


    return 0;
}
