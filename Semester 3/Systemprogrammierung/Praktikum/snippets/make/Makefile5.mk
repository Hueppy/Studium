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
.PHONY: all
all: main

main: $(OBJS)

.PHONY: clean
clean:
	rm -rf main $(OBJS) *.d *.~


##
## Abhaengigkeiten
##
%.d: %.c
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.c=.d)
