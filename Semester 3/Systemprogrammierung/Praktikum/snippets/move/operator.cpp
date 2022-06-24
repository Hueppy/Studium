/*
 * operator.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 operator.cpp`
 *
 */

#include <iostream>

using namespace std;

struct Foo {
    int val;

    Foo(int i) : val(i) {
        cout << "Konstruktor: " << i << endl;
    }
};

Foo operator+(const Foo &left, const Foo &right) {
    cout << "operator+ (Copy-Semantik): " << left.val << "+" << right.val << endl;
    return left.val + right.val;
}

/*
Foo operator+(Foo &&left, Foo &&right) {
   cout << "operator+ (Move-Semantik): " << left.val << "+" << right.val << endl;
   left.val += right.val;
   return left;
}
*/

int main() {
    Foo erg = Foo(1) + Foo(2) + Foo(3) + Foo(4);
    cout << "erg: " << erg.val << endl;
}
