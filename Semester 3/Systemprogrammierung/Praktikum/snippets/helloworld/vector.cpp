/*
 * vector.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// C++11 - mit Option --std=c++11 kompilieren!
// g++ --std=c++11 vector.cpp

int main() {
    vector<int> v(10);
    vector<double> meinVektor = {1.1, 2.2, 3.3, 4.4};
    cout << "v hat die Länge " << v.size() << endl;
//    cout << "v hat die Länge " << v.length() << endl;    // length() nur bei Strings!
    //    cout << "ohne Überprüfung: '" << v[100] << "'" << endl;
    //    cout << "mit Überprüfung: '" << v.at(100) << "'" << endl;
    cout << endl;


    vector<double> andererVektor;
    andererVektor = meinVektor;
    meinVektor[2] = 42.42;
    cout << "Zuweisung erzeugt Kopien" << endl;
    cout << "meinVektor[2]: " << meinVektor[2] << endl;
    cout << "andererVektor[2]: " << andererVektor[2] << endl;
    cout << endl;


    vector<int> meineDaten;      // initiale Groesse: 0
    cout << "meineDaten hat die Länge " << meineDaten.size() << endl;
    meineDaten.push_back(123);   // Wert anhaengen
    meineDaten.push_back(123);   // Wert anhaengen
    cout << "meineDaten hat die Länge " << meineDaten.size() << endl;
    cout << "meineDaten[0]: " << meineDaten[0] << endl;

    meineDaten.pop_back(); // Wert loeschen
    meineDaten.empty();    // leer?
    cout << "meineDaten hat die Länge " << meineDaten.size() << endl;
    cout << "meineDaten ist leer: " << (meineDaten.empty() ? "ja" : "nein") << endl;

    return EXIT_SUCCESS;
}
