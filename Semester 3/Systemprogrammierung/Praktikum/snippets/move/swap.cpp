/*
 * swap.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 swap.cpp`
 *
 */

#include <iostream>
#include <string>

using namespace std;


template<typename T>
void swapCopy(T &a, T &b) {
    T tmp{a};
    a = b;
    b = tmp;
}

template<typename T>
void swapMove(T &a, T &b) {
    T tmp{move(a)};
    a = move(b);
    b = move(tmp);
}


class X {
public:
    X() : value(42) {}

    X(const X &m) : value(m.value) {
        cout << "\t Copy-Konstruktor" << endl;
    }

    X &operator=(const X &m) {
        cout << "\t Copy-Zuweisungsoperator" << endl;
        if (this != &m) {
            value = m.value;
        }
        return *this;
    }

    X(X &&m) : value(move(m.value)) {
        cout << "\t Move-Konstruktor" << endl;
        m.value = 0;        // Defaultwert setzen
    }

    X &operator=(X &&m) {
        cout << "\t Move-Zuweisungsoperator" << endl;
        if (this != &m) {
            value = move(m.value);
            m.value = 0;    // Defaultwert setzen
        }
        return *this;
    }

private:
    int value;  // Stellen Sie sich hier was "grosses" vor :-)
};


int main() {
    X a;
    X b;

    cout << "Copy-Semantik" << endl;
    swapCopy(a, b);

    cout << "Move-Semantik" << endl;
    swapMove(a, b);
}
