/*
 * bigthree.cpp
 *
 * Author: Carsten Gips
 *
 * g++ bigthree.cpp -std=c++11
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Foo {
public:
    const Foo &bar(const vector<Foo> &a) {
        return a[0];
    }

    Foo() {
        cout << "\tDefault-Konstruktor" << endl;
    }
    Foo(const char *s) {
        cout << "\tKonstruktor mit Parameter" << endl;
    }
    Foo(const Foo &f) {
        cout << "\tCopy-Konstruktor" << endl;
    }
    Foo &operator=(const Foo &d) {
        cout << "\tZuweisungsoperator " << endl;
        return *this;
    }
    ~Foo() {
        cout << "\tDestruktor" << endl;
    }
};


int main() {
    Foo f;
    vector<Foo> a {"hello", "world", ":)"};

    cout << "\n\n============================================\n";
    Foo s1 = f.bar(a);
    const Foo &s2 = f.bar(a);
    Foo &s3 = f.bar(a);
    Foo s4;
    s4 = f.bar(a);
    cout << "============================================\n\n\n";

    return EXIT_SUCCESS;
}
