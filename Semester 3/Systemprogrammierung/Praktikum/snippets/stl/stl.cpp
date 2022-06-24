/*
 * stl.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ stl.cpp -std=c++11`
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    // Elemente in einen Vektor packen
    vector<int> v = {9, 8, 6, 7};
    v.push_back(3);
    v.push_back(4);
    v.push_back(3);
    v.push_back(1);



    // for-each-Algorithmus
    cout << endl << "for-each-Algorithmus und Funktions-Pointer" << endl;
    for_each(v.begin(), v.end(), ausgabe);

    cout << endl << "for-each-Algorithmus und Funktions-Objekt" << endl;
    ausgabe_einfach a;
    for_each(v.begin(), v.end(), a);



    // count-if-Algorithmus, braucht Praedikat
    cout << endl << "Zaehlen aller geraden Elemente mit Funktions-Objekt" << endl;
    test t;
    cout << count_if(v.begin(), v.end(), t) << endl;



    // Funktionsobjekt, was den Ausgabestrom als Attribut speichert
    ausgabe_kompl ak(cout);

    // Sortieren
    cout << endl << "Sortieren aller Elemente" << endl;
    sort(v.begin(), v.end());
    for_each(v.begin(), v.end(), ak);


    // Praedikate: negate, Transformation mit transform
    cout << endl << "Negieren aller Elemente mit STL-Praedikat" << endl;
    transform(v.begin(), v.end(), v.begin(), negate<int>());
    for_each(v.begin(), v.end(), ak);


    return EXIT_SUCCESS;
}
