/*
 * assert.cpp
 *
 * Author: Carsten Gips
 *
 * g++ assert.cpp
 * g++ -DNDEBUG assert.cpp
 */

#include <iostream>

using namespace std;

//#define NDEBUG
#include <cassert>

int main() {
    int a = 1, b = 42;

    cout << "assert mit true" << endl;
    assert(a < b);

    cout << "assert mit false" << endl;
    assert(b < a);

    cout << "verlasse Programm ..." << endl;
    return 0;
}
