/*
 * chrono.cpp
 *
 * Author: Carsten Gips
 *
 * g++ -std=c++11 chrono.cpp
 *
 */

#include <chrono>
#include <time.h>

#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    // Systemzeit
    chrono::system_clock::time_point timeNow = chrono::system_clock::now();
    time_t t = time(NULL);
    cout << "C++: nanoseconds since 1.1.1970: " << timeNow.time_since_epoch().count() << endl;
    cout << "C:       seconds since 1.1.1970: " << t << endl;


    // Startzeit
    chrono::system_clock::time_point start = chrono::system_clock::now();
    // do something: sleep für 2s
    sleep(2);
    // Endzeit
    chrono::system_clock::time_point end = chrono::system_clock::now();
    // Dauer berechnen
    cout << "Dauer: " << chrono::duration<double>(end - start).count() << " [s]" << endl;


    // typedef für Minuten, Sekunden und Millisekunden
    using myminutes = chrono::duration<long long, ratio<60>>;
    using myseconds = chrono::duration<long long, ratio<1>>;
    using mymilliseconds = chrono::duration<long long, ratio<1, 1000>>;

    myseconds sec(5);
    myminutes min(2);
    mymilliseconds mil(10);

    mymilliseconds milRes = min + sec + mil;
    cout << "2min + 5s + 10ms = " << milRes.count() << "ms" << endl;


    // Eigene Zeitberechnungen
    using mylecture = chrono::duration<double, ratio<90 * 60>>; // VL hat 90 Minuten a 60 Sekunden
    myminutes m(45);
    mylecture lect(m);
    cout << "45 Minuten sind " << lect.count() << " Vorlesungen" << endl;


    // Zeitakrobatik :)
    chrono::duration<int, ratio<24 * 60 * 60> > one_day(1);
    chrono::system_clock::time_point today = chrono::system_clock::now();
    chrono::system_clock::time_point tomorrow = today + one_day;

    t = chrono::system_clock::to_time_t(today);
    cout << "Jetzt:  " << ctime(&t);
    t = chrono::system_clock::to_time_t(tomorrow);
    cout << "Morgen: " << ctime(&t);


    return EXIT_SUCCESS;
}
