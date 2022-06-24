/*
 * bind.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ bind.cpp -std=c++11`
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>   // std::bind

using namespace std;
using namespace std::placeholders;    // adds visibility of _1, _2, _3, ...


double foo(double a, double b) {
    cout << "a: " << a << ", b: " << b << "\t => ";
    return a + b;
}

void f(int v1, int v2, int v3, int v4, int v5) {
    cout << "v1: " << v1 << ", v2: " << v2 << ", v3: " << v3 << ", v4: " << v4 << ", v5: " << v5 << endl << endl;
}

template<typename T>
bool bar(const T &v1, const T &v2) {
    cout << "v1: " << v1 << ", v2: " << v2 <<  "\t => ";
    return v1 == v2;
}


int main() {
    // Elemente in einen Vektor packen
    vector<int> v = {3, 4, 6, 3};



    // Platzhalter f. beide Argumente
    function<double(double, double)> foo1 = bind(foo, _1, _2);
    cout << "Beide Argumente ungebunden:                " << foo1(1.9, 3.1) << endl;

    // Platzhalter f. erstes Argument: _1
    // Zweites Argument an den Wert 2.2 gebunden
    function<double(double)> foo2 = bind(foo, _1, 2.2);
    cout << "Zweites Argument an den Wert 2.2 gebunden: " << foo2(1.9) << endl;

    // Platzhalter f. zweites Argument: _1 (!)
    // Erstes Argument an den Wert 1.1 gebunden
    function<double(double)> foo3 = bind(foo, 1.1, _1);
    cout << "Erstes Argument an den Wert 1.1 gebunden:  " << foo3(3.1) << endl;

    // Beide Argumente gebunden
    function<double()> foo4 = bind(foo, 1.1, 2.2);
    cout << "beide Argumente gebunden:                  " << foo4() << endl << endl;



    // Reihenfolge beim Binden
    // in f(): v1=_2, v2=42, v3=_1, v4=7, v5=_2
    // in f1(): _1=1, _2=2
    // Resultat: v1=2, v2=42, v3=1, v4=7, v5=2
    int n = 7;
    function<void(int,int)> f1 = bind(f, _2, 42, _1, n, _2);
    n = 42;
    f1(1, 2);



    // Templatefunktion gebunden ...
    function<bool(int)> bar4 = bind(bar<int>, _1, 4);
    cout << "Templatefunktion gebunden:                 ";
    cout << bar4(1) << endl;

    cout << "Zaehlen aller Elemente==4 mit Funktionspointer und gebundenem Parameter: " << endl;
    cout << count_if(v.begin(), v.end(), bar4) << endl;


    return EXIT_SUCCESS;
}
