/*
 * main.cpp
 *
 * Author: Carsten Gips
 *
 */

#include <iostream>
#include <cstdlib>

#include "header.h"

using namespace std;


namespace {
    int i;
}

/*
extern int i;  // statt anon. namespace: Warnung: undefinierter Verweis auf »i«
*/


int main() {
    cout << "main: i: " << i++ << endl;
    cout << "main: k: " << k++ << endl;
    a();
    b();
    cout << endl;

    cout << "main: i: " << i++ << endl;
    cout << "main: k: " << k++ << endl;
    a();
    b();
    cout << endl;

    cout << "main: i: " << i++ << endl;
    cout << "main: k: " << k++ << endl;
    a();
    b();
    cout << endl;

    return EXIT_SUCCESS;
}
