/*
 * defaultKonstruktor.cpp
 *
 * Author: Carsten Gips
 *
 *  g++ -c --std=c++11 defaultKonstruktor.cpp
 */

class Dummy {
public:
    Dummy() = default;

    Dummy(int a) {
        value = a;
    }

    Dummy(const Dummy &a) = delete;

private:
    int value;

    Dummy &operator=(const Dummy &d);
};
