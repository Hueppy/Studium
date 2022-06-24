/*
 * customallocator.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ customallocator.cpp -std=c++11`
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


template<typename T>
class my_allocator {
public:
    using value_type = T;  // typedef T value_type;

    my_allocator() {}

    template<typename U>
    my_allocator(const my_allocator<U> &) {}

    T *allocate(size_t n) {
        return allocator<T>().allocate(n);
//        return static_cast<T *>(malloc(n * sizeof(T)));
    }

    void deallocate(T *p, size_t n) {
        allocator<T>().deallocate(p, n);
//        free(p);
    }
};

template<typename T, typename U>
bool operator==(const my_allocator<T> &, const my_allocator<U> &) { return true; }

template<typename T, typename U>
bool operator!=(const my_allocator<T> &, const my_allocator<U> &) { return false; }


int main() {
    cout << "\t Lege Standard-Allokator für mystring an ..." << endl;
    my_allocator<mystring> myalloc;
    allocator_traits<my_allocator<mystring>> myalloctrait;

    cout << "\t Reserviere Speicher für 3 mystring ..." << endl;
    mystring *str = myalloc.allocate(3);
//    mystring *str = myalloctrait.allocate(myalloc, 3);

    cout << "\t Baue die 3 mystrings ..." << endl;
    myalloctrait.construct(myalloc, str, "wuppie");
    myalloctrait.construct(myalloc, str + 1, " fluppie");
    myalloctrait.construct(myalloc, str + 2, " :-)");

    cout << str[0] << str[1] << str[2] << endl;

    cout << "\t Destruiere die 3 mystrings ..." << endl;
    myalloctrait.destroy(myalloc, str);
    myalloctrait.destroy(myalloc, str + 1);
    myalloctrait.destroy(myalloc, str + 2);

    cout << "\t Gebe Speicher frei (für alle 3 mystrings) ..." << endl;
    myalloc.deallocate(str, 3);
//    myalloctrait.deallocate(myalloc, str, 3);


    return EXIT_SUCCESS;
}
