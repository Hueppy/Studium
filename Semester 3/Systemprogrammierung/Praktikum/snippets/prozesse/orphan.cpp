/*
 * orphan.cpp
 *
 * Author: Carsten Gips
 */

#include <unistd.h>       // fork(), getpid()
#include <cstdio>         // perror()
#include <cstdlib>        // abort()

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    pid_t p;

    p = fork();

    if (p == 0) {
        /* child */
        cout << "Kindprozess: PID: " << getpid() << ", PPID: " << getppid() << endl;
        cout << endl << "Kind: Eltern-PID: " << getppid() << endl;
        sleep(18);  /* Zeit zum Zeigen der neuen Eltern-PID */
        cout << endl << "Kind: Eltern-PID: " << getppid() << endl;
        cout << "Ende Kind" << endl;
        exit(EXIT_SUCCESS);

    } else if (p > 0) {
        /* parent */
        cout << "Elternprozess: PID: " << getpid() << ", PPID: " << getppid() << endl;
        sleep(2);   /* gib dem Kind-Prozess genug Zeit, den echten Eltern kennenzulernen */
        cout << "Ende Eltern (vor Kind!)" << endl;
        exit(EXIT_SUCCESS);

    } else {
        /* error */
        perror("fork");
        exit(EXIT_FAILURE);
    }

}
