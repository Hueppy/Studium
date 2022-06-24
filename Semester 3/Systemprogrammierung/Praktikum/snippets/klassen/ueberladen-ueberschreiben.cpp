/*
 * ueberladen-ueberschreiben.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Person {
public:
    Person(const string &n = "") : name(n) {}

    string toString() const {
        return string("(Person) name: ") + name;
    }

    string toString(string a) const {
        return string("(Person) a: ") + a;
    }

    void f() {
        cout << "Person::f()" << endl;
    }

    void f(char c) {
        cout << "Person::f(char)" << endl;
    }

private:
    string name;
};


class Student : public Person {
public:
    Student(const string &name = "", const string &n = "") : Person(name), nick(n) {}

    string toString() const {
        return string("(Student) ") + Person::toString() + " => Nickname: " + nick;
    }

    void f(double d) {
        cout << "Student::f(double)" << endl;
    }

private:
    string nick;
};


int main() {
    Person p("Bob");
    Student s("Heinz", "heizer");

    cout << "s.toString:            " << s.toString() << endl << endl;
//    cout << "s.toString(a):         " << s.toString("huhu") << endl;
//    cout << "s.Person::toString(a): " << s.Person::toString("huhu") << endl;

//    cout << "s.f: "; s.f('a');
//    cout << "s.f: "; s.Person::f('a');

    return EXIT_SUCCESS;
}
