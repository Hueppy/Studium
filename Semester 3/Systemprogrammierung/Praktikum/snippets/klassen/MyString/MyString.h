/*
 * MyString.h
 *
 * Author: Carsten Gips
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_

#include <iostream>
#include <string>

using namespace std;


class MyString {
public:
    MyString(const char *s = "");
    MyString(const MyString &);
    ~MyString();

    string toString() const;

    MyString &operator=(const MyString &);
    MyString &operator+=(const MyString &);
    MyString operator+(const MyString &);
    bool operator!=(const MyString &);

    MyString &operator++();
    MyString operator++(int);

private:
    size_t len;
    char *str;

    void copy(const char *);
    void revert();

    friend ostream &operator<<(ostream &, const MyString &);
};

#endif /* MYSTRING_H_ */
