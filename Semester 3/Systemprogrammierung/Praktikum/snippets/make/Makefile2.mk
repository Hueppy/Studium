## Author: Carsten Gips <carsten.gips@fh-bielefeld.de>
##


##
## Regeln
##
all: tollesProgramm

tollesProgramm: fkt.o main.o
	gcc -o tollesProgramm fkt.o main.o

fkt.o: fkt.c fkt.h
	gcc -c -Wall -ansi -pedantic fkt.c

main.o: main.c fkt.h
	gcc -c -Wall -ansi -pedantic main.c

clean:
	rm -rf tollesProgramm fkt.o main.o *.~
