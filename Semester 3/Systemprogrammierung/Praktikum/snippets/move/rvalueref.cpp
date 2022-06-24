/*
 * rvalueref.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 rvalueref.cpp`
 *
 */

#include <iostream>
#include <string>

using namespace std;


string foo(int&) {
    return "lvalue reference";
}
string foo(const int&) {
    return "const lvalue reference";
}
string foo(int&&) {
    return "rvalue reference";
}


int main() {
    int x1 = 42;
    const int x2 = 7;

    // Lvalues können nur an (konstante) Lvalue-Referenzen binden
    int& y1 = x1;
    const int& y2 = x1;
    int&& y3 = x1;                          // error: rvalue reference to type 'int' cannot bind to lvalue of type 'int'

    // Konstante Lvalues können nur an konstante Lvalue-Referenzen binden
    int& v1 = x2;                           // error: binding value of type 'const int' to reference to type 'int' drops 'const' qualifier
    const int& v2 = x2;
    int&& v3 = x2;                          // error: binding value of type 'const int' to reference to type 'int' drops 'const' qualifier

    // Rvalues können an konstante Lvalue-Referenzen oder an Rvalue-Referenzen gebunden werden, wobei letztere stärker binden
    int& z1 = x1 + 7;                       // error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
    const int& z2 = x1 + 7;                 // const lvalue reference extends lifetime
    int&& z3 = x1 + 7;                      // rvalue reference extends lifetime


    // Bindungsregeln am Funktionsaufruf demonstriert
    // Tipp: Aufrufe auch mit auskommentierter Funktion string foo(int&&) testen!
    cout << "foo(x1): " << foo(x1) << endl; // lvalue bound to lvalue reference (C++98)
    cout << "foo(x2): " << foo(x2) << endl; // const lvalue bound to const lvalue reference (C++98)
    cout << "foo(7):  " << foo(7) << endl;  // rvalue reference binds stronger (C++11)
}
