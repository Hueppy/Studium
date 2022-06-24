/*
 * vererbungAbstrakt.cpp
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

    const string &getName() const { return name; }

    virtual string toString() const = 0;

private:
    string name;
};


string Person::toString() const {
    return string("(Person.toString) Name: ") + name;
}


class Student : public Person {
public:
    Student(const string &name = "", double c = 0.0) : Person(name), credits(c) {}

    string toString() const {
        return Person::toString() + string("(Student.toString) ... ");
    }

private:
    double credits;
};


int main() {
    Person p("Holger");
    Student s("Heinz", 10.0);
    cout << endl << s.toString() << endl << endl;

    return EXIT_SUCCESS;
}
