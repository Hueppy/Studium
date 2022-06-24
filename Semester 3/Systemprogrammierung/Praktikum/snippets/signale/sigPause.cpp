/*
 * sigPause.cpp
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
void sigHupHandler(int sig) {
    if (sig == SIGHUP) {
        cout << endl << "SIGHUP" << endl << endl;
    }
}

void multiSigHandler(int sig) {
    if (sig == SIGCHLD) {
        cout << endl << "SIGCHLD" << endl << endl;
    } else if (sig == SIGINT) {
        cout << endl << "SIGINT" << endl << endl;
    }
}


int main(int argc, char *argv[]) {
    // PID ausgeben
    cout << endl << "meine PID: " << getpid() << endl << endl;

    // Signalhandler registrieren
    cout << "Registriere Signalhandler fuer SIGHUP (1)" << endl;
    if (signal(SIGHUP, sigHupHandler) == SIG_ERR) {
        PANIC("SIGHUP-Handler");
    }
    cout << "Signalhandler fuer SIGHUP (1) erfolgreich registriert" << endl;

    // Signalhandler registrieren
    cout << "Registriere Signalhandler fuer SIGINT (2)" << endl;
    if (signal(SIGINT, multiSigHandler) == SIG_ERR) {
        PANIC("SIGINT-Handler");
    }
    cout << "Signalhandler fuer SIGINT (2) erfolgreich registriert" << endl;

/*
    // Ignoriere SIGINT
    cout << "ignoriere SIGINT (2)" << endl;
    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        PANIC("SIGINT-Handler");
    }
    cout << "SIGINT (2) ignoriert" << endl;
*/

    // Warten auf behandelte (oder beendende) Signale
    while (1) {
        cout << "\t while-Schleife (vor pause)" << endl;
        pause();    // wartet auf behandelte/beendende Signale
        cout << "\t while-Schleife (nach pause)" << endl;
    }

}
