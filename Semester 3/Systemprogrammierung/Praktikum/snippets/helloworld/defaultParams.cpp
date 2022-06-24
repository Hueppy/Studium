/*
 * defaultParams.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <cstdlib>

using namespace std;


void foo();
void bar(void);

void defaultParams(int i, int j = 7, int k = 42);


int main() {
//    foo(1); // in C erlaubt; NICHT in C++
//    bar(1); // geht in C auch nicht

    cout << "Aufruf defaultParams(2)" << endl;
    defaultParams(2);

    cout << "Aufruf defaultParams(2, 10)" << endl;
    defaultParams(2, 10);

    cout << "Aufruf defaultParams(2, 10, 21)" << endl;
    defaultParams(2, 10, 21);

    return EXIT_SUCCESS;
}


// Defaultparameter aus der Deklaration werden in der Definition nicht wiederholt
void defaultParams(int i, int j, int k) {
    cout << "i: " << i << endl;
    cout << "j: " << j << endl;
    cout << "k: " << k << endl;
    cout << endl;
}


void foo() {}
void bar(void) {}
