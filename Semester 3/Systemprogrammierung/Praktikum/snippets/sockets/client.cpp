/*
 * client.cpp
 *
 * Author: Carsten Gips
 */

// Disclaimer:
// Der Code dient zur Veranschaulichung der in der VL besprochenen Sachverhalte
// und enthaelt nicht ansatzweise die noetigen Pruefungen auf Fehlerfaelle etc.!
//
// g++ -std=c++11 -o client client.cpp
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>
#include <cstdio>          // perror()
#include <cstdlib>         // abort()

#include <iostream>
#include <string>

using namespace std;

#define DEBUG(x)    cout << "Debug: " << x << endl
#define PANIC(msg)  {perror(msg); abort();}
#define SRVADDR     "127.0.0.1"
#define MAXBUF      1024
#define MYPORT      15151

int main() {
    // Socket aufmachen
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // IP und Port setzen
    sockaddr_in name;
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    inet_aton("127.0.0.1", &(name.sin_addr));   // bei "echten" Adressen auf Fehler pruefen!
    name.sin_port = htons(MYPORT);              // Port 15151

    // Connect zum Server
    DEBUG("Client: versuche connect");
    connect(fd, (struct sockaddr *) &name, sizeof(name));

    // Fertigmachen zum Senden
    int n;
    char buf[MAXBUF];
    memset(buf, 0, MAXBUF);
    sprintf(buf, "%s", "Hallo Welt!");
    n = -1;
    n = send(fd, buf, strlen(buf), 0);
    DEBUG("Client: n=" << n << " Bytes gesendet");
    DEBUG("Client: Botschaftslaenge: " << strlen(buf));
    DEBUG("Client: Gesendete Botschaft: \n>>>" << buf << "<<<\n\n");

    // Antwort vom Server empfangen
    memset(buf, 0, MAXBUF);
    n = -1;
    n = recv(fd, buf, MAXBUF, 0);
    DEBUG("Client: n=" << n << " Bytes gelesen:");
    DEBUG("Client: Botschaftslaenge: " << strlen(buf));
    DEBUG("Client: Empfangene Botschaft: \n>>>" << buf << "<<<");

    // Sockets schliessen
    DEBUG("Client: schliesse Socket");
    close(fd);

    return 0;
}
