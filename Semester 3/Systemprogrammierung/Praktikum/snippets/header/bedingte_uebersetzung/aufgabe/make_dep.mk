## Author: Carsten Gips <carsten.gips@fh-bielefeld.de>
##


##
## Variablen
##
CC       = gcc
CFLAGS   = -g -Wall -ansi -pedantic
SRC      = $(wildcard *.c)
OBJS     = $(SRC:.c=.o)


##
## Regeln
##
all: main

main: $(OBJS)

clean:
	rm -rf main $(OBJS) *.~ *.d


##
## Abhaengigkeiten
##
%.d: %.c
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.c=.d)


##
## PHONY
##
.PHONY: all clean
