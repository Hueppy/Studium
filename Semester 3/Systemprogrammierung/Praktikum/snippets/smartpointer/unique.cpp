/*
 * unique.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 unique.cpp`
 *
 */

#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;


class Dummy {
public:
    Dummy(int v = 0) : val(v) {
        cout << "Dummy(int v): v=" << val << ", Adresse: " << (void *) this << endl;
    }

    ~Dummy() {
        cout << "~Dummy(): v=" << val << ", Adresse: " << (void *) this << endl;
    }

    int getVal() { return val; }

private:
    int val;
};


void printPtr(const string &s, const unique_ptr <Dummy> &uPtr) {
    cout << s;
    cout << (*uPtr).getVal();
    cout << ", Adresse: " << (void *) (uPtr.get());
    cout << endl;
}


int main() {
    // Standardkonstruktor
    unique_ptr <Dummy> uPtr;
    if (!uPtr) {
        cout << "\t uPtr: noch nicht gültig! (!uPtr)" << endl;
    }
    if (uPtr == nullptr) {
        cout << "\t uPtr: noch nicht gültig! (uPtr == nullptr)" << endl;
    }
    cout << endl;

    // Initialisierung
    Dummy *d = new Dummy;
    unique_ptr <Dummy> uPtr0{d};              // FALSCH! (nicht RAII)
    unique_ptr <Dummy> uPtr1{new Dummy(11)};  // Korrekt: RAII
//    delete d;                                 // FALLE!!!!
    printPtr("\t uPtr0 (Init): ", uPtr0);
    printPtr("\t uPtr1 (Init): ", uPtr1);
    cout << endl;

    // KEINE Copy-Semantik vorhanden
//    unique_ptr<Dummy> uPtr2a(uPtr0);            // ERROR!
//    unique_ptr<Dummy> uPtr2b;  uPtr2b = uPtr0;  // ERROR!

    // Move-Konstruktor
    unique_ptr <Dummy> uPtr3{new Dummy(33)};
    unique_ptr <Dummy> uPtr4{move(uPtr1)};
    if (!uPtr1) {
        cout << "\t uPtr1 (Move-Ctor): nicht mehr gültig!" << endl;
    }
    printPtr("\t uPtr4 (Move-Ctor): ", uPtr4);
    cout << endl;

    // Move-Zuweisung
    unique_ptr <Dummy> uPtr5;
    uPtr5 = move(uPtr4);
    if (!uPtr4) {
        cout << "\t uPtr4 (Move-Assignment): nicht mehr gültig!" << endl;
    }
    printPtr("\t uPtr5 (Move-Assignment): ", uPtr5);
    cout << endl;

    // Zugriff auf Resource
    Dummy *dp = uPtr5.get();
    Dummy &dr = *uPtr5;

    // Resource explizit freigeben
    dp = uPtr5.release();
    if (!uPtr5) {
        cout << "\t uPtr5 (Release): nicht mehr gültig!" << endl;
    }
    delete dp;
    cout << endl;

    // Resource ersetzen
    printPtr("\t uPtr0 (vor Reset):  ", uPtr0);
    uPtr0.reset(new Dummy(42));
    printPtr("\t uPtr0 (nach Reset): ", uPtr0);
    cout << endl;

    // Resourcen vertauschen
    printPtr("\t uPtr0 (Swap): ", uPtr0);
    printPtr("\t uPtr3 (Swap): ", uPtr3);
    uPtr0.swap(uPtr3);
    printPtr("\t uPtr0 (Swap): ", uPtr0);
    printPtr("\t uPtr3 (Swap): ", uPtr3);
    cout << endl;
}
