/*
 * streamManip.cpp
 *
 * Author: Carsten Gips
 */

#include <ios>
#include <iomanip>
#include <iostream>

using namespace std;


class Leerzeilen {
public:
    Leerzeilen(int i = 1) : anzahl(i) {
    }

    ostream &operator()(ostream &ostr) const {  // Funktionsoperator
        for (int i = 0; i < anzahl; i++) {
            ostr << ":" << setw(5) << right << i << ":" << '\n';
        }
        ostr.flush();
        return ostr;
    }

private:
    int anzahl;
};


ostream &operator<<(ostream &ostr, const Leerzeilen &leerz) {
    return leerz(ostr); // leerz ist ein Funktionsobjekt :)
}


int main() {
    cout << "Anfang" << endl << Leerzeilen(12) << "Ende" << endl;

    return 0;
}
