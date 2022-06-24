/*
 * funktionsobjekt.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ funktionsobjekt.cpp -std=c++11`
 *
 */

#include <iostream>

using namespace std;


// einfache Ausgabefunktion
void ausgabe(int i) {
    cout << i << endl;
}


// Ausgabe mit einem Funktionsobjekt
class ausgabe_einfach {
public:
    void operator()(int i) {
        cout << i << endl;
    }
};


// Ausgabe mit Funktionsobjekt, was den Stream als Attribut haelt
class ausgabe_kompl {
public:
    ausgabe_kompl(ostream &s) : os(s), nr(0) {}

    void operator()(int i) {
        os << "Ausgabe Nr.: " << nr << ", Wert: " << i << endl;
        ++nr;
    }

private:
    ostream &os;
    int nr;
};


// Funktionsobjekt als Prädikat
class test {
public:
    bool operator()(int i) {
        return (i % 2) == 0;
    }
};


int main() {
    // Funktionsobjekt
    test wuppie;
    bool fluppie = wuppie(3);
    cout << "Wert: " << fluppie << endl;


    // Funktion
    ausgabe(42);

    // nochmal, mit Funktionsobjekt
    ausgabe_einfach a;
    a(42);


    // Ausgabe mit komplexerem Funktionsobjekt
    ausgabe_kompl ax(cout);
    ax(7);
    ax(42);
    ax(99);


    return EXIT_SUCCESS;
}
