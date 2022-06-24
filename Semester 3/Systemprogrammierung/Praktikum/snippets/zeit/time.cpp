/*
 * time.cpp
 *
 * Author: Carsten Gips
 */

#include <time.h>
#include <sys/times.h>

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    time_t t;
    struct tm *loc;
    char buf[1024];

    // Sekunden seit 1970
    t = time(NULL);
    cout << "time:     " << t << endl;

    // System-Format: bereits mit Umbruch
    cout << "ctime:    " << ctime(&t);

    // Umrechnen in Jahre, Wochen, Tage, ...
    loc = localtime(&t);
    // eigene Formatierung
    strftime(buf, 1024, "%A, %d %b %Y, %H:%M:%S %Z", loc);
    cout << "strftime: " << buf << endl;

    // Greenwich
    loc = gmtime(&t);
    // eigene Formatierung
    strftime(buf, 1024, "%A, %d %b %Y, %H:%M:%S %Z", loc);
    cout << "strftime: " << buf << endl;

    return EXIT_SUCCESS;
}
