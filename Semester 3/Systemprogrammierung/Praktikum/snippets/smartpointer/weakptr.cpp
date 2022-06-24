/*
 * weakptr.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 weakptr.cpp`
 *
 */

#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    weak_ptr<int> weakPtr;
    cout << weakPtr.use_count() << endl;
    cout << weakPtr.expired() << endl << endl;

    shared_ptr<int> sharedPtr1(new int(42));
    weakPtr = sharedPtr1;
    cout << weakPtr.use_count() << endl;
    cout << weakPtr.expired() << endl;
    cout << sharedPtr1.use_count() << endl;
//    cout << "*weakPtr: " << *weakPtr << endl;   // NICHT vorhanden => lock() nutzen
    cout << "*sharedPtr1: " << *sharedPtr1 << endl << endl;

    shared_ptr<int> sharedPtr2 = weakPtr.lock();
    cout << weakPtr.use_count() << endl;
    cout << weakPtr.expired() << endl;
    cout << sharedPtr1.use_count() << endl;
    cout << sharedPtr2.use_count() << endl << endl;
}
