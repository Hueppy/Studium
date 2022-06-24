/*
 * foo.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 foo.cpp`
 *
 */

#include <iostream>

using namespace std;


class Bar {
public:
    Bar() { cout << "Bar::Bar()" << endl; }

    Bar(const Bar &) { cout << "Bar::Bar(const Bar&)" << endl; }

    Bar(Bar &&) { cout << "Bar::Bar(Bar&&)" << endl; }

    Bar &operator=(const Bar &rhs) {
        cout << "operator=(const Bar&)" << endl;
        return *this;
    }

    Bar &operator=(Bar &&rhs) {
        cout << "operator=(Bar&&)" << endl;
        return *this;
    }
};


class Foo {
public:
    Foo(Bar &i) : val(i) { cout << "Foo::Foo(Bar&)" << endl; }

    Foo(const Foo &rhs) : val(rhs.val) { cout << "Foo::Foo(const Foo&)" << endl; }

    Foo(Foo &&rhs) : val(move(rhs.val)) { cout << "Foo::Foo(Foo &&)" << endl; } // Bar::Bar(Bar&&)
//    Foo(Foo &&rhs) : val(rhs.val) { cout << "Foo::Foo(Foo &&)" << endl; }       // Bar::Bar(const Bar&) ...

    template<typename T>
    void setVal(T &&p) { val = forward<T>(p); }     // operator=(const Bar&); operator=(Bar&&)
//    void setVal(T &&p) { val = p; }                 // operator=(const Bar&); operator=(Bar&)
private:
    Bar val;
};

Foo operator+(Foo &&lhs, const Foo &rhs) {
    cout << "operator+" << endl;
    return move(lhs);  // move lhs into return value (if move ctor available, otherwise copy lhs)
//    return lhs;        // copy lhs into return value
}


int main() {
    cout << "\t creating Bar" << endl;
    Bar b;

    cout << endl << "\t creating Foo" << endl;
    Foo f{b};

    cout << endl << "\t creating Foo w/ lvalue" << endl;
    Foo f1{f};

    cout << endl << "\t creating Foo w/ rvalue" << endl;
    Foo f2{move(f1)};

    cout << endl << "\t setting value" << endl;
    f.setVal(b);
    f.setVal(Bar());

//    cout << endl << "\t call to operator+" << endl;
//    Foo erg = Foo(b) + Foo(f);
}
