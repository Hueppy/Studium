/*
 * swap2.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 swap2.cpp`
 *
 */

#include <iostream>

using namespace std;


template<typename T>
void swap2(T &a, T &b) {
    T tmp{move(a)};
    a = move(b);
    b = move(tmp);
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
    swap2(a, b);

    cout << "Move-Semantik" << endl;
    swap2(c, d);
}
