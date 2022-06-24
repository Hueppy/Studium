//============================================================================
// Name        : trCpp.cpp
// Author      : Carsten Gips
// Description : Taschenrechner in C++, ANSI-Style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
//#include <stdlib.h>   // exit()
#include <cstdlib>      // exit()

using namespace std;

namespace BLUB {
    void opsEinlesen(int d, int *array) {
        cout << "\tBLUB::opsEinlesen: " << d << " Operanden eingeben" << endl;
        for (int i = 0; i < d; i++) {
            cin >> array[i];
        }
    }
}

namespace WUPPIE {
    void opsEinlesen(int d, vector<int> *array) {
        // Hinweis: Der Pointer wird in C++ als unschön betrachtet -- die bessere
        // Alternative ist eine C++-Referenz, über die wir noch sprechen werden!
        int zahl;

        cout << "\tWUPPIE::opsEinlesen: " << d << " Operanden eingeben" << endl;
        for (int i = 0; i < d; i++) {
            cin >> zahl;
            (*array)[i] = zahl;     // ohne Bereichspruefung!
//            array->push_back(zahl); // erweitert den Vector gegebenenfalls
        }
    }
}

int main() {
    string buf;
    int erg, d;
    int *ops;
//    vector<int> ops;    // initial 0 Elemente
//    vector<int> ops(d); // initial d Elemente

    while (cin >> buf) {
        if (buf == "print") {
            cout << "\tErgebnis: " << erg << endl;

        } else if (buf == "sum") {

            cin >> d;
            try {
                ops = new int[d];
            } catch (...) {
                cerr << "Oops, kein Speicher ..." << endl;
                exit(EXIT_FAILURE);
            }

            BLUB::opsEinlesen(d, ops);      // geht nur mit int*
//            WUPPIE::opsEinlesen(d, &ops);   // geht nur mit vector<int>*

            erg = 0;
            for (int i = 0; i < d; i++) {
//            for (int i=0; i<ops.size(); i++) {  // geht nur bei vector
                cout << "\tZwischensumme: " << erg << ", Operand: " << ops[i] << ", Index: " << i << endl;
                erg += ops[i];
//                erg += ops.at(i);   // mit Bereichspruefung (nur bei vector)
            }

            delete[] ops;

        } else if (buf == "end") {
            return EXIT_SUCCESS;

        } else {
            cout << "Unbekannte Eingabe" << endl;
        }
    }

    return EXIT_SUCCESS;
}
