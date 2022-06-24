/*
 * constexpr.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ constexpr.cpp -std=c++14`
 *
 */

#include <iostream>

using namespace std;


constexpr int f(int x) { return x * x; }

constexpr int ff(int x) { return f(f(x)); }


class Wuppie {
public:
    constexpr Wuppie(int a, int b) : v1(a), v2(b) {}

    constexpr int getSum() { return v1 + v2; }

private:
    int v1;
    int v2;
};


int main() {
    // Nutzung von konstanten Ausdruecken (zur Compile-Zeit berechnet)
    constexpr int x = 42;
    constexpr int y = ff(10);
    constexpr int z = Wuppie(7, x).getSum();

    // Test: Ist das wirklich `constexpr`? => Fehlermeldung darf nicht erscheinen
    static_assert(x == 42, "nicht constexpr");
    static_assert(y == 10000, "nicht constexpr");
    static_assert(z == 49, "nicht constexpr");
    static_assert(f(10) == 100, "nicht constexpr");
    static_assert(ff(x) == 3111696, "nicht constexpr");
    static_assert(Wuppie(7, x).getSum() == 49, "nicht constexpr");


    // Geht auch herkoemmlich (zur Laufzeit ausgewertet/berechnet)
    int xd = 42;
    int yd = ff(10);
    int zd = Wuppie(7, xd).getSum();

    // Test: Ist das wirklich `constexpr`? => Fehlermeldung MUSS erscheinen
//    static_assert(xd == 42, "nicht constexpr");
//    static_assert(yd == 10000, "nicht constexpr");
//    static_assert(zd == 49, "nicht constexpr");
}
