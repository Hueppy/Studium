/*
 * variablentemplate.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ variablentemplate.cpp -std=c++14`
 *
 */

#include <iostream>

using namespace std;


// Definition der Template-Variablen PI
// Typ von PI wird erst bei Nutzung bestimmt!
template<typename T> T PI = T{3.141592653589793285};

// Template-Funktion mit Einsatz der Template-Variablen PI
// Flaecheninhalt Kreis = PI * r^2
template<typename T>
T flaeche_kreis(T r) {
    return PI<T> * r * r;
}


int main() {
    double flaeche = flaeche_kreis(2.0);
    cout << "Flaeche: " << flaeche << " (Radius: 2.0)" << endl;
}
