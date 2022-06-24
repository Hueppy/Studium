/*
 * copy-on-write.cpp
 *
 * Author: Carsten Gips
 */

#include <unistd.h>       // fork(), getpid()
#include <cstdio>         // perror()
#include <cstdlib>        // abort()

#include <iostream>

using namespace std;

int global_var = 1;

int main(int argc, char *argv[]) {
    pid_t p;
    int lokal_var = 1;

    p = fork();
    if (p == 0) {
        /* child */
        sleep(1);   /* Kurze Pause */

        cout << "Kind: global_var = " << global_var << " (Adressse: " << &global_var << ")" << endl;
        cout << "Kind: lokal_var  = " << lokal_var  << " (Adressse: " << &lokal_var  << ")" << endl << endl;

        ++global_var;
        ++lokal_var;

        cout << "Kind: global_var = " << global_var << " (Adressse: " << &global_var << ")" << endl;
        cout << "Kind: lokal_var  = " << lokal_var  << " (Adressse: " << &lokal_var  << ")" << endl << endl;

        exit(EXIT_SUCCESS);

    } else if (p > 0) {
        /* parent */
        cout << "Eltern: global_var = " << global_var << " (Adressse: " << &global_var << ")" << endl;
        cout << "Eltern: lokal_var  = " << lokal_var  << " (Adressse: " << &lokal_var  << ")" << endl << endl;

        sleep(3); /* Kurze Pause */

        cout << "Eltern: global_var = " << global_var << " (Adressse: " << &global_var << ")" << endl;
        cout << "Eltern: lokal_var  = " << lokal_var  << " (Adressse: " << &lokal_var  << ")" << endl << endl;

        exit(EXIT_SUCCESS);

    } else {
        /* error */
        perror("fork");
        exit(EXIT_FAILURE);
    }

}
