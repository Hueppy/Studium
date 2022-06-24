/*
 * relOps.cpp
 *
 * Author: Carsten Gips
 * nach einer Idee von rel_ops
 * Quelle rel_ops: www.cplusplus.com/reference/utility/rel_ops/
 */

#include <iostream>
#include <string>

using namespace std;

namespace rel_ops {
    template<class T>
    bool operator!=(const T &x, const T &y) {
        return !(x == y);
    }

    template<class T>
    bool operator>(const T &x, const T &y) {
        cout << "RelOps: >" << endl;
        return y < x;
    }

    template<class T>
    bool operator<=(const T &x, const T &y) {
        return !(y < x);
    }

    template<class T>
    bool operator>=(const T &x, const T &y) {
        return !(x < y);
    }
}

class Person {
public:
    Person(const string &n) : name(n) {
    }

    bool operator<(const Person &rhs) const {
        cout << "Person: <" << endl;
        return name < rhs.name;
    }

private:
    string name;
};

using namespace rel_ops;

int main() {
    Person a("Anne"), b("Herbert");

    cout << boolalpha;
    cout << "a<b: " << (a < b) << endl;
    cout << "a>b: " << (a > b) << endl;

    return 0;
}
