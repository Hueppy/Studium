/*
 * swap3.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 swap3.cpp`
 *
 */

#include <iostream>

using namespace std;


template<typename T>
void swap3(T &&a, T &&b) {
    T tmp{a};
    a = b;
    b = tmp;
}


class X {
public:
    X() {}

    X(const X &m) {
        cout << "\t X::Copy-Konstruktor" << endl;
    }

    X &operator=(const X &m) {
        cout << "\t X::Copy-Zuweisungsoperator" << endl;
        return *this;
    }
};

class Y {
public:
    Y() {}

    Y(Y &&m) {
        cout << "\t Y::Move-Konstruktor" << endl;
    }

    Y &operator=(Y &&m) {
        cout << "\t Y::Move-Zuweisungsoperator" << endl;
        return *this;
    }
};


int main() {
    X a, b;
    Y c, d;

    cout << "Copy-Semantik" << endl;
    swap3(a, b);

    cout << "Move-Semantik" << endl;
    swap3(c, d);
}
