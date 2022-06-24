/*
 * funcvoid.cpp
 *
 * Author: Carsten Gips
 *
 * `g++ -Wall funcvoid.cpp`
 *
 */

#include <iostream>
#include <cstdlib>

using namespace std;


int f1(void);
int f2();
int f3();


int main() {
    /* legaler Gebrauch */
    f1();
    f2();

    /* falscher Gebrauch */
    f1(42);     /* Compiler: Fehler: too many arguments to function ‘int f1()’ */
    f2(42);     /* Compiler: Fehler: too many arguments to function ‘int f2()’ */
    f3();       /* Linker: Fehler: undefinierter Verweis auf ‘f3()‘            */
    f3(42, 43); /* Compiler: Fehler: too many arguments to function ‘int f3()’ */

    return EXIT_SUCCESS;
}


int f1(void) {
    cout << "Huhu von f1" << endl;
    return EXIT_SUCCESS;
}

int f2() {
    cout << "Huhu von f2" << endl;
    return EXIT_SUCCESS;
}

int f3(int a) {
    cout << "Huhu von f3: a=" << a << endl;
    return EXIT_SUCCESS;
}


// Legal in C++
// Deklaration: wuppie() hat KEINE Parameter!
// Definition:  Funktionsüberladung mit wuppie(int) ...
int wuppie();
int wuppie(int x) { return x; }

// Legal in C++
// Deklaration: fluppie() hat KEINE Parameter!
// Definition:  Funktionsüberladung mit fluppie(int) ...
int fluppie(void);
int fluppie(int x) { return x; }
