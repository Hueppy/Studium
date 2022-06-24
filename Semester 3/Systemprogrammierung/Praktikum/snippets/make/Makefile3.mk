## Author: Carsten Gips <carsten.gips@fh-bielefeld.de>
##


##
## Variablen
##
CC       = gcc
CFLAGS   = -g -Wall -ansi -pedantic
OBJS     = fkt.o main.o


##
## Regeln
##
all: tollesProgramm

tollesProgramm: $(OBJS)
	$(CC) -o $@ $^

fkt.o: fkt.c fkt.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c fkt.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf tollesProgramm $(OBJS) *.~
