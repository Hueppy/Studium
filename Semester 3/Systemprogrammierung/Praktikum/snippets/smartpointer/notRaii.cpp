/*
 * notRaii.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 notRaii.cpp`
 *
 */

#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;


class Dummy {
public:
    Dummy(int v = 0) : val(v) {
        cout << "Dummy(int v): v=" << val << ", Adresse: " << (void *) this << endl;
    }

    ~Dummy() {
        cout << "~Dummy(): v=" << val << ", Adresse: " << (void *) this << endl;
    }

    int getVal() { return val; }

private:
    int val;
};


int main() {
    cout << boolalpha;

    Dummy *d1 = new Dummy(5);
    Dummy *d2 = d1;

    shared_ptr <Dummy> sp1(d1);
    shared_ptr <Dummy> sp2(d2);

    cout << "sp1.unique(): " << sp1.unique() << endl;
    cout << "sp2.unique(): " << sp2.unique() << endl;

    sp1.reset();
    *sp2;           // AUTSCH!!!
}
