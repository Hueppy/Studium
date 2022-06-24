/*
 * cin.cpp
 *
 * Author: Carsten Gips
 */

#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    // liest alle Ziffern bis zum ersten Nicht-Ziffernzeichen
    // (fuehrende Whitespaces werden ignoriert!)
    int zahl;
    cin >> zahl;
    cout << "Gelesener int: '" << zahl << "'\n";

//    // einzelne Zeichen (auch Whitespaces) lesen
//    char c; cin.get(c);
//    cout << "Gelesener char: '" << c << "'\n";
//
//    // Eingabe: "100  12.4[Enter]"
//    int i; double d; cin >> i >> d;
//    cout << "Gelesen: int '" << i << "'; double '" << d << "'\n";
//
//    // Eingabe "Hallo Welt" liest nur "Hallo"
//    string myString; cin >> myString;
//    cout << "Gelesen string: '" << myString << "'\n";
//
//    // liest komplette Zeile (bis zum Enter)
//    string myString;
//    getline(cin, myString);
//    cout << "Gelesene Zeile: '" << myString << "'\n";

    return EXIT_SUCCESS;
}
