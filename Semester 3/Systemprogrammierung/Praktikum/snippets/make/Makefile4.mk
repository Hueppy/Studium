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
all: main

main: $(OBJS)

clean:
	rm -rf main $(OBJS) *.~
