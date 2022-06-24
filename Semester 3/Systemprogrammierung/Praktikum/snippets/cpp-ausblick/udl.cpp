/*
 * udl.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include<iomanip>

using namespace std;


/*
ACHTUNG: UDL funktioniert nur mit diesen Parametern (Auswahl):
    char const*
    unsigned long long
    long double
    char const*, std::size_t
    wchar_t const*, std::size_t
    char16_t const*, std::size_t
    char32_t const*, std::size_t

Rückgabetypen sind nicht eingeschränkt!

vgl. https://en.cppreference.com/w/cpp/language/user_literal
*/


// Kilogramm: rechnet in Gramm um
long double operator "" _kg(unsigned long long x) {
    return x * 1000.0;
}

long double operator "" _kg(long double x) {
    return x * 1000.0;
}

// Gramm: "Basiseinheit"
long double operator "" _g(long double x) {
    return x;
}

// Milligramm: rechnet nach Gramm um
long double operator "" _mg(long double x) {
    return x / 1000.0;
}


int main(int argc, char *argv[]) {
    double weight = 42_kg;
    cout << "42_kg sind " << weight << "_g" << endl;
    cout << setprecision(12) << "42_kg + 7.9_mg sind " << (weight + 7.9_mg) << "_g" << endl;


    return EXIT_SUCCESS;
}
