/*
 * cppScope.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <cstdlib>

using namespace std;

int a = 1, b = 2;

int main() {
    cout << "a: " << a << endl;

    int a = 10;
    cout << "a: " << a << endl;
    cout << "::a: " << ::a << endl;

    int b = 9;
    {
        cout << endl;

        int a = 999;
        cout << "a: " << a << endl;
        cout << "::a: " << ::a << endl;

        int b = 20;
        cout << endl;
        cout << "b: " << b << endl;
        cout << "::b: " << ::b << endl;

        int c = 300;
        cout << "c: " << c << endl;
    }

    cout << endl;
    cout << "a: " << a << endl;
    cout << "::a: " << ::a << endl;
    cout << "b: " << b << endl;
    cout << "::b: " << ::b << endl;
//    cout << "c: " << c << endl;  // welches "c"?!

    return EXIT_SUCCESS;
}
