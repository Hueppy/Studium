/*
 * shared.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 shared.cpp`
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


void printPtr(const string &s, const shared_ptr <Dummy> &sPtr) {
    cout << s;
    cout << (*sPtr).getVal();
    cout << ", Use_Count: " << sPtr.use_count();
    cout << " (Unique: " << sPtr.unique() << ")";
    cout << ", Adresse: " << (void *) (sPtr.get());
    cout << endl;
}


int main() {
    // Standardkonstruktor
    shared_ptr <Dummy> sPtr;
    if (!sPtr) {
        cout << "\t sPtr: noch nicht gültig! (!sPtr)" << endl;
    }
    if (sPtr == nullptr) {
        cout << "\t sPtr: noch nicht gültig! (sPtr == nullptr)" << endl;
    }
    cout << endl;

    // Initialisierung
    Dummy *d = new Dummy;
    shared_ptr <Dummy> sPtr0{d};              // FALSCH! (nicht RAII)
    shared_ptr <Dummy> sPtr1{new Dummy(11)};  // Korrekt: RAII
//    delete d;                                 // FALLE!!!!
    printPtr("\t sPtr0 (Init): ", sPtr0);
    printPtr("\t sPtr1 (Init): ", sPtr1);
    cout << endl;

    // Copy-Semantik vorhanden
    shared_ptr <Dummy> sPtr2a(sPtr0);
    shared_ptr <Dummy> sPtr2b;  sPtr2b = sPtr0;
    printPtr("\t sPtr0 (Copy): ", sPtr0);
    printPtr("\t sPtr2a (Copy): ", sPtr2a);
    printPtr("\t sPtr2b (Copy): ", sPtr2b);
    cout << endl;

    // Move-Konstruktor
    shared_ptr <Dummy> sPtr3{new Dummy(33)};
    shared_ptr <Dummy> sPtr4{move(sPtr1)};
    if (!sPtr1) {
        cout << "\t sPtr1 (Move-Ctor): nicht mehr gültig!" << endl;
    }
    printPtr("\t sPtr4 (Move-Ctor): ", sPtr4);
    cout << endl;

    // Move-Zuweisung
    shared_ptr <Dummy> sPtr5;
    sPtr5 = move(sPtr4);
    if (!sPtr4) {
        cout << "\t sPtr4 (Move-Assignment): nicht mehr gültig!" << endl;
    }
    printPtr("\t sPtr5 (Move-Assignment): ", sPtr5);
    cout << endl;

    // Zugriff auf Resource
    Dummy *dp = sPtr5.get();
    Dummy &dr = *sPtr5;

    // Resource explizit freigeben
    sPtr5.reset();
    if (!sPtr5) {
        cout << "\t sPtr5 (Reset): nicht mehr gültig!" << endl << endl;
    }
    cout << endl;

    // Resource ersetzen
    printPtr("\t sPtr0 (vor Reset):  ", sPtr0);
    sPtr0.reset(new Dummy(42));
    printPtr("\t sPtr0 (nach Reset): ", sPtr0);
    cout << endl;

    // Resourcen vertauschen
    printPtr("\t sPtr0 (Swap): ", sPtr0);
    printPtr("\t sPtr3 (Swap): ", sPtr3);
    sPtr0.swap(sPtr3);
    printPtr("\t sPtr0 (Swap): ", sPtr0);
    printPtr("\t sPtr3 (Swap): ", sPtr3);
    cout << endl;
}
