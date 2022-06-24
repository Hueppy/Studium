/*
 * auto.cpp
 *
 * Author: Carsten Gips
 *
 * g++ -std=c++11 auto.cpp
 * g++ -std=c++14 auto.cpp
 *
  */

#include <iostream>

using namespace std;


// vor C++14
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}


/*
// seit C++14
template<typename T1, typename T2>
auto add(T1 a, T2 b) {
    return a + b;
}
*/


int main() {
    int    x = add(7, 42);
    double y = add(1.0, 2.1);

    return EXIT_SUCCESS;
}
