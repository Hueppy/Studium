/*
 * atexit.cpp
 *
 * Author: Carsten Gips
 */

#include <cstdlib>    // atexit()

#include <iostream>

using namespace std;

class D {
public:
    ~D() { cout << endl << "AUTSCH! (Destruktor Klasse D)" << endl << endl; }
};

class S {
public:
    ~S() { cout << endl << "AUTSCH! (Destruktor Klasse S)" << endl << endl; }
};

void f1() { cout << "Welt, ich muss dich lassen ... (f1)" << endl; }

void f2() { cout << "Röchel (f2)" << endl; }

void f3() {
    static int cnt = 0;
    cout << "und tschüss ... (f3; call no." << ++cnt << ")" << endl;
}

void f4() {
    D d;
    static S s;
    cout << "(f4)" << endl;
//    abort();
//    exit(0);
    return;
}


int main() {
    cout << "!!!Hello World!!!\n" << endl;

    D d;
    static S s;

//    f4();

//    atexit(f1);
//    atexit(f3);
//    atexit(f2);
//    atexit(f3);

    cout << "verlasse Programm ...\n" << endl;

//    abort();
//    exit(0);
    return 0;
}
