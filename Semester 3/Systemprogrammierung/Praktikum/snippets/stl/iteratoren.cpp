/*
 * iteratoren.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ iteratoren.cpp -std=c++11`
 *
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};



    // C++98
    cout << endl << "herkoemmliche for-Schleife" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;


    cout << endl << "for-Schleife mit Iteratoren" << endl;
    vector<int>::const_iterator iter;
    for (iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter << ", ";
    }
    cout << endl;

    vector<int>::iterator iter2 = v.begin();
    *(iter2 + 2) = 42;
    for (iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter << ", ";
    }
    cout << endl;



    // C++11
    cout << endl << "for-Schleife (C++11)" << endl;
    for (int &x : v) {
        x *= 2;
    }
    for (int x : v) {
        cout << x << ", ";
    }
    cout << endl;


    return EXIT_SUCCESS;
}
