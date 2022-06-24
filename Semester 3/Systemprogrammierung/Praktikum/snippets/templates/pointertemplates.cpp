/*
 * pointertemplates.cpp
 *
 * Author: Carsten Gips
 */

#include <string>
#include <iostream>

using namespace std;


template<class T>
struct C {
    C(T x) : t(x) { cout << "standard template" << endl; }

    T t;
};

/*
template <class T>
struct C<T*> {
    C(T* x) : t(x) { cout << "T* template" << endl; }

    T* t;
};
*/

/*
template <>
struct C<int*> {
    C(int* x) : t(x) { cout << "int* template" << endl; }

    int* t;
};
*/



int main() {
    string s = "oh";
    C<string> a(string("a"));
    C<string*> b(&s);
    C<int*> c(new int);
}
