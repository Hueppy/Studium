## Author: Carsten Gips <carsten.gips@fh-bielefeld.de>
##


##
## Variablen
##
CC       = gcc
CFLAGS   = -g -Wall -ansi -pedantic
OBJS     = ledbar.o main.o


##
## Regeln
##
all: main

main: $(OBJS)
	$(CC) -o $@ $^

ledbar.o: ledbar.c ledbar.h ledbar_intern.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c ledbar.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf main $(OBJS) *.~
