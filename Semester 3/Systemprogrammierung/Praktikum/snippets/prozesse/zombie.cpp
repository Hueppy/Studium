/*
 * zombie.cpp
 *
 * Author: Carsten Gips
 */

#include <unistd.h>       // fork(), getpid()
#include <cstdio>         // perror()
#include <cstdlib>        // abort()
#include <sys/wait.h>

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    pid_t p;

    p = fork();

    if (p == 0) {
        /* child */
        cout << "Kindprozess: PID: " << getpid() << ", PPID: " << getppid() << endl;
//        sleep(10);

        cout << "*quiek* Ende Kind *quiek*" << endl;
        exit(42);
//        exit(EXIT_SUCCESS);
//        exit(EXIT_FAILURE);
//        abort();

    } else if (p > 0) {
        /* parent */
        cout << "Elternprozess: PID: " << getpid() << ", PPID: " << getppid() << endl;
        sleep(60);

/*
        cout << "Eltern: warte auf Ende von Kind" << endl;
        int status;
        int pid = wait(&status);
        if (pid == -1) {
            perror("wait");     // keine Kindprozesse mehr!
        }

        if (WIFEXITED(status)) cout << "Kind normal terminiert mit Status " << WEXITSTATUS(status) << endl;
        if (WIFSIGNALED(status)) cout << "Kind abgeschossen mit Signal " << WTERMSIG(status) << endl;
        sleep(20);

        cout << "Eltern: warte auf Ende von weiterem Kind" << endl;
        pid = wait(&status);
        if (pid == -1) {
            perror("wait");     // keine Kindprozesse mehr!
        }

        cout << "*roechel* Ende Eltern *roechel*" << endl;
        exit(EXIT_SUCCESS);
*/

    } else {
        /* error */
        perror("fork");
        exit(EXIT_FAILURE);
    }

}
