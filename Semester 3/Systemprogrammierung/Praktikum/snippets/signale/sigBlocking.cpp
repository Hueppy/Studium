/*
 * sigBlocking.cpp
 *
 * Author: Carsten Gips
 */

//#include <signal.h>   // C-Variante der Bibliothek
#include <csignal>      // C++-Variante; eine reicht!
                        // signal(), kill(), raise(),

#include <unistd.h>     // pause(), sleep(), getpid()
#include <cstdio>       // perror()
#include <cstdlib>      // abort()

#define PANIC(msg)  {perror(msg); abort();}

#include <iostream>

using namespace std;

// Signalhandler
static void mySignalHandler(int sig) {
    cout << endl << "caught signal no. " << sig << endl;
    for (int i = 0; i < 10; i++) {
        cout << "hdl for sig " << sig << " loop " << i << endl;
        sleep(1);
    }
    cout << endl;
}


int main(int argc, char *argv[]) {
    // PID ausgeben
    cout << endl << "meine PID: " << getpid() << endl << endl;

    // Signalhandler registrieren
    cout << "Registriere Signalhandler fuer SIGHUP (1)" << endl;
    if (signal(SIGHUP, mySignalHandler) == SIG_ERR) {
        PANIC("SIGHUP-Handler");
    }
    cout << "Signalhandler fuer SIGHUP (1) erfolgreich registriert" << endl;

    // Signalhandler registrieren
    cout << "Registriere Signalhandler fuer SIGINT (2)" << endl;
    if (signal(SIGINT, mySignalHandler) == SIG_ERR) {
        PANIC("SIGINT-Handler");
    }
    cout << "Signalhandler fuer SIGINT (2) erfolgreich registriert" << endl;

    while (1) {
        cout << "\t start while-Schleife" << endl;
        pause();    // wartet auf behandelte Signale

/*
        cout << "\t blocking Signal SIGINT (2)" << endl;
        sigset_t mySet;
        sigemptyset(&mySet);
        sigaddset(&mySet, SIGINT);
        if (sigprocmask(SIG_SETMASK, &mySet, NULL) < 0) {
            PANIC("blocking SIGINT (2)");
        }

        cout << "\t main(): warte auf behandeltes Signal ..." << endl;
        pause();    // wartet auf behandelte Signale

        cout << "\t unblocking Signal SIGINT (2)" << endl;
        sigemptyset(&mySet);
        sigaddset(&mySet, SIGINT);
        if (sigprocmask(SIG_UNBLOCK, &mySet, NULL) < 0) {
            PANIC("unblocking SIGINT (2)");
        }
*/

    }

}
