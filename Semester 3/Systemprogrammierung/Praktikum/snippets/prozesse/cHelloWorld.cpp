/*
 * cHelloWorld.c
 *
 * Author: Carsten Gips
 *
 * `g++ -Wall cHelloWorld.cpp -o cHelloWorld`
 *
 */

#include <stdio.h>
#include <unistd.h>         // fork(), getpid()
#include <iostream>

using namespace std;


int main() {
    // C++-Style Comment ...
    printf("Hello World from C  :-)\n");
    cout << "Hello World-Prozess: PID: " << getpid() << ", PPID: " << getppid() << endl;

    return 0;
}
