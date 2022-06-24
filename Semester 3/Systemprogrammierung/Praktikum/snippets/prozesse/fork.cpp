/*
 * fork.cpp
 *
 * Author: Carsten Gips
 */

#include <unistd.h>       // fork(), getpid()
#include <stdio.h>        // perror()
#include <stdlib.h>       // abort()

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    pid_t p;
    int a = 99;

    p = fork();

    a += p;     /* wird im Kind- und Elternprozess verschiedene Werte bekommen */

    if (p == 0) {
        /* child */
        cout << "Kindprozess: a=" << a << " (p: " << p << ", PID: " << getpid() << ", PPID: " << getppid() << ")" << endl;
        cout << "Ende Kind" << endl;
        exit(EXIT_SUCCESS);

    } else if (p > 0) {
        /* parent */
        cout << "Elternprozess: a=" << a << " (p: " << p << ", PID: " << getpid() << ", PPID: " << getppid() << ")" << endl;
        cout << "Eltern: sleep(10)" << endl;
        sleep(10);
        cout << "Ende Eltern" << endl;
        exit(EXIT_SUCCESS);

    } else {
        /* error */
        perror("fork");
        exit(EXIT_FAILURE);
    }

}
