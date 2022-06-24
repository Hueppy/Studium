/*
 * templateSpezialisierungen.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>

using namespace std;


// Primaeres (allgemeines) Template
template<unsigned line, unsigned column>
class Matrix {
public:
    Matrix();
};

// Partiell spezialisiertes Template
template<unsigned line>
class Matrix<line, 1> {
public:
    Matrix();
};

// Vollstaendig spezialisiertes Template
template<>
class Matrix<3, 3> {
public:
    Matrix();
};


int main() {
    Matrix<3, 4> matrix;        // allg. Template
    Matrix<20, 1> vector;       // partiell spez. Templ.
    Matrix<3, 3> dreiKreuzDrei; // vollst. spez. Templ.
}


template<unsigned line, unsigned column>
Matrix<line, column>::Matrix() { cout << "allgemeines Template" << endl; }

template<unsigned line>
Matrix<line, 1>::Matrix() { cout << "partiell spezialisiertes Template" << endl; }

Matrix<3, 3>::Matrix() { cout << "vollstaendig spezialisiertes Template" << endl; }
