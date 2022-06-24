/*
 * a.cpp
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

void a(void) {
    cout << "a: i:    " << i++ << endl;
    cout << "a: k:    " << k++ << endl;
}
