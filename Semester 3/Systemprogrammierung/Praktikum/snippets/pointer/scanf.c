/*
 * scanf.c
 *
 * Author: Carsten Gips
 *
 * `gcc -Wall scanf.c`
 *
 */

#include<stdio.h>

int main(void) {
    int alter, d, m, y, x;

    printf("Wie alt bist Du? ");
    x = scanf("%d", &alter);
    printf("\n%d Wert(e) gelesen\n\n", x);
    printf("Du bist %d Jahre alt.\n", alter);

    printf("\nGeburtsdatum (xx|xxxx|xxxx) ");
    x = scanf("%d|%d|%d", &d, &m, &y);
    printf("\n%d Wert(e) gelesen\n\n", x);
    printf("Du hast am %d.%d.%d Geburtstag\n", d, m, y);

    return 0;
}
