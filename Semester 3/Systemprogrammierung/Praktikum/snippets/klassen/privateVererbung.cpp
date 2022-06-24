/*
 * privateVererbung.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <cstdlib>

using namespace std;


class DeepThought {
public:
    int berechnen() {
        return zahl * 42;
    }

protected:
    int zahl;
};


class Antwort {
public:
    virtual int erfragen() {
        return EXIT_SUCCESS;
    }

    virtual ~Antwort() {
    }
};


class UltimativeAntwort : public Antwort, private DeepThought {
                              // Interface        Implementation
public:
    int erfragen() {
        zahl = 1;
        return berechnen();
    }
};


int main() {
    Antwort *antwort = new UltimativeAntwort();
    cout << antwort->erfragen() << endl;
    delete antwort;

    return EXIT_SUCCESS;
}
