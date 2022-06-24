/*
 * cppEnums.cpp
 *
 * Author: Carsten Gips
 */

// C++11 - mit Option --std=c++11 kompilieren!
// g++ --std=c++11 cppEnums.cpp

#include <cstdlib>
#include <iostream>

using namespace std;


// klassische Enums
enum Wochentag {
    sonntag, montag, dienstag, mittwoch
};
enum Farbe {
    rot = 0, gruen = 1, blau, gelb = 5, orange
};


// neu in C++11: Klassen-Enums
enum class WochentagC {
    sonntag, montag = 9, dienstag, mittwoch
};
enum class FarbeC : unsigned char {
    rot, gruen, blau, gelb, orange
};


int main() {
    Wochentag feierTag = sonntag;

    Farbe color = rot;
    int meineFarbe = blau;
    cout << meineFarbe << endl; // 2
    cout << orange << endl;     // 6

    Farbe mischung;
//    mischung = gruen+rot;       // nicht erlaubt!
    int mix = gruen + rot;        // das geht :-)
    if (mischung > gelb)          // das geht auch ...
        mischung = rot;


    // Klassen erzeugen Namespaces ...
    WochentagC feierTagK = WochentagC::sonntag;  // geht mit einfachen Enums nicht: Jedes Symbol nur 1x im Programm sonst!
    FarbeC colorK = FarbeC::rot;                 // `rot` haben wir 2x: in `Farbe` und in `FarbeC`

    return EXIT_SUCCESS;
}
