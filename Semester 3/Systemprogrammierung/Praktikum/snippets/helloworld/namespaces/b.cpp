/*
 * b.cpp
 *
 * Author: Carsten Gips
 *
 */

#include <iostream>
#include <cstdlib>

#include "header.h"

using namespace std;


namespace {
    int i;
}

void b(void) {
    cout << "b: i:    " << i++ << endl;
    cout << "b: k:    " << k++ << endl;
}
