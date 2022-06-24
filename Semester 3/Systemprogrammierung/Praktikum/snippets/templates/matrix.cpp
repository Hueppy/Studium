/*
 * matrix.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Object>
class Matrix {
public:
    Matrix(unsigned rows = 1, unsigned cols = 1);

    const vector <Object> &operator[](unsigned row) const;

private:
    vector <vector<Object>> xyField;
};

int main() {
//    Matrix m;     // Problem: Matrix ist ein Klassen-Template!
    Matrix<int> m1;
    Matrix<double> m2(12, 3);
    Matrix<string> m3;
}

template<typename Object>
Matrix<Object>::Matrix(unsigned rows, unsigned cols) {
    cout << "rows: " << rows << ", cols: " << cols << endl;
}
