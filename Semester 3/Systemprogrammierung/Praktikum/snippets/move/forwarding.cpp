/*
 * forwarding.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 forwarding.cpp`
 *
 */

#include <iostream>

using namespace std;


// Dummy-Klasse
class X {
};


// Verarbeitet Lvalues
void foo(const X &lval) {
    cout << "Lvalue" << endl;
}

// Verarbeitet Rvalues
void foo(X &&rval) {
    cout << "Rvalue" << endl;
}

// Templatefunktion, die Parameter weitergibt an konkrete Funktionen
template<typename T>
void bar(T &&p) {
    foo(p);
}


int main() {
    X a;

    foo(a);
    foo(move(a));
    foo(X());

    bar(a);
    bar(move(a));
    bar(X());
}
