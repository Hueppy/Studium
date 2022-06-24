/*
 * string.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    string a, b("ich bin b");
    a = "ich bin a";
    cout << a << ", " << b << endl;
    cout << a[2] << endl;
    cout << "a hat die Länge " << a.size() << endl;
    cout << "a hat die Länge " << a.length() << endl;
    //    cout << "ohne Überprüfung: '" << a[100] << "'" << endl;
    //    cout << "mit Überprüfung: '" << a.at(100) << "'" << endl;
    cout << endl;


    string stringKopie(a);
    cout << "a: '" << a << "'" << endl;
    cout << "stringKopie: '" << stringKopie << "'" << endl;

    a = "wuppie";
    cout << "a: '" << a << "'" << endl;
    cout << "stringKopie: '" << stringKopie << "'" << endl;
    cout << endl;

    string nochEiner("neuer string namens nochEiner");
    stringKopie = nochEiner;
    cout << "nochEiner: '" << nochEiner << "'" << endl;
    cout << "stringKopie: '" << stringKopie << "'" << endl;

    nochEiner = "was ganz anderes";
    cout << "nochEiner: '" << nochEiner << "'" << endl;
    cout << "stringKopie: '" << stringKopie << "'" << endl;
    cout << endl;


    stringKopie += b;
    stringKopie = "123" + stringKopie;
//    stringKopie = "123" + "456";            // nicht erlaubt!!
//    stringKopie = "123" + 9;                // Vorsicht!!!
    cout << "Konkatenieren geht auch: '" << stringKopie << "'" << endl;
    cout << endl;


    if (stringKopie != "123") {
        cout << "String '" << stringKopie << "' ist nicht gleich '123'" << endl;
    }

    stringKopie = "123";
    if (stringKopie == "123") {
        cout << "String '" << stringKopie << "' ist gleich '123'" << endl;
    }

    return EXIT_SUCCESS;
}
