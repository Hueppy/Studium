/*
 * movesemantics.cpp
 *
 * Author: Carsten Gips
 *
 *  `g++ -std=c++11 movesemantics.cpp`
 *
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s1 = "ABC";
    string s2;
    string s3;

    cout << "s1: '" << s1 << "', \ts2: '" << s2 << "', \ts3: '" << s3 << "'" << endl;

    s2 = s1;            // Copy-Semantik: Inhalt von s1 wird *kopiert*
    cout << "s1: '" << s1 << "', \ts2: '" << s2 << "', \ts3: '" << s3 << "'" << endl;

    s3 = std::move(s1); // Move-Semantik: Inhalt von s1 wird *verschoben*
    cout << "s1: '" << s1 << "', \ts2: '" << s2 << "', \ts3: '" << s3 << "'" << endl;
}
