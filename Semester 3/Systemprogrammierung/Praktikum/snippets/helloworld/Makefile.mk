# Author: Carsten Gips <carsten.gips@fh-bielefeld.de>



## Default-Target
all: tollesProgramm

## Baue "tollesProgramm"
tollesProgramm: cHelloWorld.c
	gcc -o tollesProgramm cHelloWorld.c

## Lasse das Programm laufen
run: tollesProgramm
	./tollesProgramm

## Aufraeumen
clean:
	rm -rf tollesProgramm
