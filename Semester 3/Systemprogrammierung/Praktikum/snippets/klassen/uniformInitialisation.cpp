/*
 * uniformInitialisation.cpp
 *
 * Author: Carsten Gips
 *
 *  g++ -Wall --std=c++11 uniformInitialisation.cpp
 */

#include <initializer_list>
#include <iostream>
#include <cstdlib>

using namespace std;

class Foo {
public:
    Foo(string s, int x) {
        cout << "Foo(string,int)" << endl;
    }

    Foo(int x, int y) {
        cout << "Foo(int,int)" << endl;
    }

    Foo(initializer_list<int> v) {
        cout << "Foo(initializer_list<int>)" << endl;
    }
};

int main() {
    // Klassischer Konstruktor, expliziter Aufruf
    Foo a(1, 2);

    // Klassischer Konstruktor, mit uniformer Initialisierung
    Foo b{"dummy", 2};

    // Sequenz-Konstruktor hat Vorrang
    Foo c{1, 2};

    return EXIT_SUCCESS;
}
