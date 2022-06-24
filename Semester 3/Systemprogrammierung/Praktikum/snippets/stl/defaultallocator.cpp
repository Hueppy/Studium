/*
 * defaultallocator.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ defaultallocator.cpp -std=c++11`
 *
 */

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class mystring {
public:
    mystring() : s() { cout << "mystring()" << endl; }

    mystring(const string &str) : s(str) { cout << "mystring(" << s << ")" << endl; }

    ~mystring() { cout << "~mystring(" << s << ")" << endl; }

private:
    string s;

    friend ostream &operator<<(ostream &, const mystring &);
};

ostream &operator<<(ostream &out, const mystring &s) {
    return out << s.s;
}


int main() {
    cout << "\t Lege Standard-Allokator für mystring an ..." << endl;
    allocator<mystring> myalloc;

    cout << "\t Reserviere Speicher für 3 mystring ..." << endl;
    mystring *str = myalloc.allocate(3);

    cout << "\t Baue die 3 mystrings ..." << endl;
    myalloc.construct(str, "wuppie");
    myalloc.construct(str + 1, " fluppie");
    myalloc.construct(str + 2, " :-)");

    cout << str[0] << str[1] << str[2] << endl;

    cout << "\t Destruiere die 3 mystrings ..." << endl;
    myalloc.destroy(str);
    myalloc.destroy(str + 1);
    myalloc.destroy(str + 2);

    cout << "\t Gebe Speicher frei (für alle 3 mystrings) ..." << endl;
    myalloc.deallocate(str, 3);


    return EXIT_SUCCESS;
}
