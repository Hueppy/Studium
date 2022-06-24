/*
 * assertStatic.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ assertStatic.cpp -std=c++11`
 *
 */

#include <iostream>

using namespace std;

template<class T>
struct Plus {
    static_assert(std::is_arithmetic<T>::value, "Plus geht nur fuer arithmetische Typen!");
};

int main() {
    // direkte Auswertung zur Compile-Zeit
    static_assert(sizeof(void *) >= 32, "wuppie");
    static_assert(sizeof(void *) >= 2, "fluppie");

    // int is arithmetic
    Plus<int> addInt = Plus<int>();

    // std::string is not arithmetic
    Plus<std::string> addString = Plus<std::string>();
}
