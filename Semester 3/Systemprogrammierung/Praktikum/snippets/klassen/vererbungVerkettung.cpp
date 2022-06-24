/*
 * vererbungVerkettung.cpp
 *
 * Author: Carsten Gips
 */


#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Person {
public:
//    Person(const string &n)
    Person(const string &n = "") : name(n) { cout << "Konstruktor Person" << endl; }

    ~Person() { cout << "Destruktor Person" << endl; }

private:
    string name;
};


class Student : public Person {
public:
    Student(const string &name = "", double c = 0.0) : Person(name), credits(c) {
        cout << "Konstruktor Student" << endl;
//        Person(name);
    }

    ~Student() { cout << "Destruktor Student" << endl; }

private:
    double credits;
};


int main() {
    {
        cout << endl << "erster Block" << endl;
        Person p("Bob");
    }

    cout << "irgendwo dazwischen" << endl;

    {
        cout << endl << "zweiter Block" << endl;
        Student s("Heinz", 10.0);
    }

    cout << "isch abe ferttisch" << endl << endl;


    return EXIT_SUCCESS;
}
