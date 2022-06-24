/*
 * perror.cpp
 *
 * Author: Carsten Gips
 */

#include <cstdio>        // perror()
#include <cerrno>        // errno
#include <unistd.h>

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int fd = -1;

    if (close(fd) == -1) {
        perror("HUHU :-)  => close hat nen Problem");
        cerr << "errno: " << errno << endl << endl;
        return -1;
    }

    return 0;
}
