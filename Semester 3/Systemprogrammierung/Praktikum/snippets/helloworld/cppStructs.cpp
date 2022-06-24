/*
 * cppStructs.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    struct person {  // Structs sind in C++ Klassen mit public Attributen/Methoden
        int alter;
        string name;

        person() {
            alter = 0;
            name = "niemand";
            cout << "Konstruktor von struct person" << endl;
        }
    } Heinz;

    person Anna;    // nur `person Anna;`, nicht `struct person Anna;`!!!
    Anna.alter = 10;
    Anna.name = "Anna";

    cout << "Heinz:\n" << "Alter: " << Heinz.alter << ", Name: " << Heinz.name << endl;

    return EXIT_SUCCESS;
}
