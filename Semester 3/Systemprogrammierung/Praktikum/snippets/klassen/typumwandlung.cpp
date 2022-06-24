/*
 * typumwandlung.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <cstdlib>

using namespace std;

class A {
public:
    virtual void f() {
        cout << "A::f()" << endl;
    }
};


class B : public A {
public:
    virtual void f() {
        cout << "B::f()" << endl;
    }
};


B *g(A *pa) {
    B *pb = dynamic_cast<B *>(pa);
    if (pb) {
        pb->f();
    }
    return static_cast<B *>(pa);
}


int main() {
    A a, *pa;
    B b, *pb;

    cout << endl << "Abgeleitete Klasse mit Basisklassenpointer" << endl;
    pa = &b;
    pb = g(pa);

    cout << endl << "Basisklasse mit Basisklassenpointer" << endl;
    pa = &a;
    pb = g(pa);        // pb undefiniert(!)

    return EXIT_SUCCESS;
}
