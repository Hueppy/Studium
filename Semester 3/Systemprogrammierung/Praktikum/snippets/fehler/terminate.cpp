/*
 * terminate.cpp
 *
 * Author: Carsten Gips
 */

#include <iostream>

using namespace std;

void termHandler() {
    // do something before abort();
    cout << "ouch! (terminate)\n\n";
}

void unexpHandler() {
    // do something before abort();
    cout << "iek! (unexpected)\n\n";
}

int main() {
//int main() throw() {
    set_terminate(termHandler);
    set_unexpected(unexpHandler);

    cout << "gleich ungefangene Exception *freu* :-)" << endl;
    throw 1;
    cout << "nach throw ..." << endl;
}
