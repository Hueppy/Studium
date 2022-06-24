/*
 * main.c
 *
 * Author: Carsten Gips
 *
 * `gcc main.c`
 *
 */

void fkt1();

void fkt2();

int main() {
    fkt1();
    fkt2();
}

void fkt1() {
    fkt2();
}

void fkt2() {
    42;
}
