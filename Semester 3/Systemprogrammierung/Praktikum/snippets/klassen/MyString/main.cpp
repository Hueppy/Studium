//============================================================================
// Name        : main.cpp
// Author      : Carsten Gips
//============================================================================

#include <iostream>
#include <cstdlib>
#include "MyString.h"

using namespace std;


int main() {
    MyString a, b("welt");
    MyString c(b);

    a = "hallo";
    cout << a << ", " << b << endl;

    c = a + " ";
    c += b;
    cout << c << endl;

    c = a + "123";
    if (c != "123") {
        cout << "String ungleich '123'" << endl;
    }


    cout << "a:   " << a << endl;
    MyString d = a++;
    cout << "a++: " << a << endl;
    cout << "d:   " << d << endl;

    cout << "b:   " << b << endl;
    MyString e = ++b;
    cout << "++b: " << b << endl;
    cout << "e:   " << e << endl;

    return EXIT_SUCCESS;
}
