/*
 * reference.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 reference.cpp`
 *
 */

#include <iostream>

using namespace std;

int &versuch(int &a, int &b) {
    return a;
}

int main() {
    int a = 10;
    int &z = versuch(a, 10);
}
