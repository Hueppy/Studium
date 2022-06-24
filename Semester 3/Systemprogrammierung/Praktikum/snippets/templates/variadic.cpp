/*
 * variadic.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ variadic.cpp -std=c++11`
 *
 */

#include <iostream>
#include <typeinfo>

using namespace std;


// Primaeres Template: Ein Argument
template<typename T>
void printInfo(T value) {
    cout << "value: " << value << " (type: " << typeid(value).name() << ", size: " << sizeof(value) << ")" << endl;
}

// Template: Mehrere Argumente
template<typename First, typename ... Rest>
void printInfo(First first, Rest ... rest) {
    printInfo(first);       // Aufruf primäre Template-Funktion
    printInfo(rest ...);    // Rekursiver Aufruf mit Template Pack Parameter
}


// Primaeres Template (wird nur aus syntaktischen Zwecken gebraucht)
template<int ...>
struct sum;

// Spezialisierung: Kein Argument ("Abbruchbedingung")
template<>
struct sum<> {
    enum { value = 0 };
//    static const int value = 0;   // Alternative zu enum
};

// Spezialisierung: Ein oder mehrere Argumente
template<int i, int ... tail>
struct sum<i, tail ...> {
    enum { value = i + sum<tail ...>::value };
//    static const int value = i + sum<tail ...>::value;     // Alternative zu enum
};


int main() {
    printInfo(true, 42, 2.3, "c11", "C++11");   // zur Laufzeit berechnet

    cout << endl << "sum<1,2,3,4,5>::value: " << sum<1, 2, 3, 4, 5>::value << endl; // vom Compiler berechnet :)

    return 0;
}
