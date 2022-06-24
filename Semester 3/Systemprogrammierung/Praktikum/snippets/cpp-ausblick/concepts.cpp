/*
 * concepts.cpp
 *
 * nach Beispielen von
 *     - https://www.heise.de/developer/artikel/C-20-Die-vier-grossen-Neuerungen-4568956.html
 *     -https://www.heise.de/developer/artikel/C-20-Zwei-Extreme-und-die-Rettung-dank-Concepts-4594834.html
 *     -https://en.cppreference.com/w/cpp/language/constraints
 *
 * C++20-komaptibler Compiler unter https://wandbox.org/
 *
  */

#include <iostream>
#include <string>
#include <cstddef>
#include <concepts>

using namespace std;


template <class T, class U>
concept Derived = is_base_of<U, T>::value;


template <class T>
concept IntLike = numeric_limits<T>::is_integer;

/*
template <typename T>
    requires IntLike<T>
auto add(T a, T b) {
    return a + b;
}
*/

/*
template <IntLike T>
auto add(T a, T b) {
    return a + b;
}
*/


/**/
template <typename T>
auto add(T a, T b) {
    return a + b;
}
/**/


int main() {
    cout << add(string("wuppie "), string("fluppie ")) << endl;
    cout << add(7, 42) << endl;
    cout << add(1.11, 2.22) << endl;
    cout << add(true, true) << endl;

    return EXIT_SUCCESS;
}
