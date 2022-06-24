/*
 * execve.cpp
 *
 * Author: Carsten Gips
 */

#include <unistd.h>         // fork(), getpid()
#include <stdio.h>          // perror()
#include <stdlib.h>         // abort()

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    pid_t p;

    p = fork();

    if (p == 0) {
        /* child */
        cout << "Kindprozess: PID: " << getpid() << ", PPID: " << getppid() << endl;
        if (execl("/bin/ls", "ls", "-ls", "/tmp", NULL) == -1) {
//        if (execl("cHelloWorld", "", NULL) == -1) {
            /* hierher kommen wir nur im Fehlerfall */
            perror("AUTSCH: exec");
            exit(EXIT_FAILURE);
        }
        cout << "Ende Kind" << endl;
        exit(EXIT_SUCCESS);

    } else if (p > 0) {
        /* parent */
        cout << "Elternprozess: PID: " << getpid() << ", PPID: " << getppid() << endl;
        cout << "Eltern: sleep(5)" << endl;
        sleep(5);
        cout << "Ende Eltern" << endl;
        exit(EXIT_SUCCESS);

    } else {
        /* error */
        perror("fork");
        exit(EXIT_FAILURE);
    }

}
