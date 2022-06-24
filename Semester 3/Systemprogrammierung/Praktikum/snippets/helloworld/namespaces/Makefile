## Author: Carsten Gips <carsten.gips@fh-bielefeld.de>
##


##
## Variablen
##
CC       = g++
CFLAGS   = -g -Wall
SRC      = $(wildcard *.cpp)
OBJS     = $(SRC:.cpp=.o)


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
%.d: %.cpp
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.cpp=.d)
