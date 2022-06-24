/*
 * server.cpp
 *
 * Author: Carsten Gips
 */

// Disclaimer:
// Der Code dient zur Veranschaulichung der in der VL besprochenen Sachverhalte
// und enthaelt NICHT ANSATZWEISE die noetigen Pruefungen auf Fehlerfaelle etc.!
//
// g++ -std=c++11 -o server server.cpp
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <cstring>
#include <cstdio>          // perror()
#include <cstdlib>         // abort()

#include <iostream>
#include <string>

using namespace std;

#define DEBUG(x)    cout << "Debug: " << x << endl
#define PANIC(msg)  {perror(msg); abort();}
#define MAXBUF      1024
#define MYPORT      15151

int main() {
    // Socket aufmachen
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // mehrere Clients koennen Port teilen, Serveradresse direkt wiederverwendbar
    // vgl. `man 2 setsockopt`
    int y = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));

    // IP und Port
    sockaddr_in name;
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // 127.0.0.1
    name.sin_port = htons(MYPORT);                  // Port 15151

    // Socket an Namen binden
    bind(fd, (const struct sockaddr *) &name, sizeof(name));
    DEBUG("Server: auf " << inet_ntoa(name.sin_addr) << ":" << MYPORT);

    // Anzahl der Verbindungen
    listen(fd, 5);

    int n = -1;
    string msg;
    char buf[MAXBUF];
    int in_fd;
    for (;;) { // Server-Schleife
        // Verbindung annehmen und blockieren, bis Verbindung
        DEBUG("\n\nServer: Warte auf Verbindung");
        in_fd = accept(fd, NULL, NULL); // Adresse vom Komm.-Partner interessiert mich nicht

        DEBUG("Server: Verbindung etabliert");
        for (;;) { // Kommunikation mit Client
            DEBUG("Server: lese Daten");
            memset(buf, 0, MAXBUF);
            n = -1;
            n = recv(in_fd, buf, MAXBUF, 0);
            DEBUG("Server: n=" << n << " Bytes empfangen");
            if (n == 0) {
                // Besser mit errno pruefen!
                DEBUG("Server: n==0 => SOCKET CLOSED ON REMOTE END?!");
                close(in_fd);  // nur den Client-Socket schliessen
                break; // raus aus der Komm.-Schleife mit Client, naechste Verbindung akzeptieren
            }
            DEBUG("Server: Empfangene Botschaft: \n>>>" << buf << "<<<\n\n");

            msg = string("Server: Deine Anfrage war: '") + buf + "'";
            n = -1;
            n = send(in_fd, msg.c_str(), msg.length(), 0);
            DEBUG("Server: n=" << n << " Bytes gesendet");
            DEBUG("Server: Laenge der Antwort: " << msg.length());
            DEBUG("Server: Gesendete Antwort: \n>>>" << msg << "<<<");
        }
    }

    // Sockets schliessen
    DEBUG("Server: schliesse Server-Socket");
    close(fd);

    return 0;
}
