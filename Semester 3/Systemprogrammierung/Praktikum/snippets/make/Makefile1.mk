## Author: Carsten Gips <carsten.gips@fh-bielefeld.de>
##


##
## Regeln
##
all: tollesProgramm

tollesProgramm: fkt.c fkt.h main.c
	gcc -o tollesProgramm -Wall -ansi -pedantic fkt.c main.c

clean:
	rm -rf tollesProgramm *.~
