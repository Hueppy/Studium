/*
 * raetsel.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 raetsel.cpp`
 *
 */

int main() {
    int i = 1;

    int &u = ++i;
    int &v = i++;

    const int &w = ++i;
    const int &x = i++;

    int &&y = ++i;
    int &&z = i++;
}
