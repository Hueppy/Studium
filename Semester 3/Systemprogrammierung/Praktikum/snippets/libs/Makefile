##
## Makefile
##
## Author: Carsten Gips
##
.PHONY: clean all



##
## macrodefinitions
##
CC       = gcc
CFLAGS   = -g -Wall -ansi -pedantic
CFLAGS  += -I.
CFLAGS  += -fpic -fPIC
LDFLAGS  = -L.
LDLIBS   = -lTest

OBJS     = testA.o testB.o

STATLIB  = libTest.a
DYNLIB   = libTest.so



##
## rules
##
all: stat dyn dynX main


## Programm ohne Bibliothek
main: $(OBJS) main.o
	$(CC) $(LDFLAGS) $^ -o $@


## Code in statischer Bibliothek, Programm dagegen linken
stat: $(STATLIB) main.o
	$(CC) $(LDFLAGS) -o $@ main.o -static $(LDLIBS)


## Code in dynamischer Bibliothek, Programm dagegen linken
## Standard-Variante: LD_LIBRARY_PATH passend setzen!
dyn: $(DYNLIB) main.o
	$(CC) $(LDFLAGS) -o $@ main.o $(LDLIBS)


## Code in dynamischer Bibliothek, Programm dagegen linken
## Alternativ-Variante: Pfad zu dyn. Lib. im Programm hart codiert!
dynX: LDFLAGS+=-Wl,-rpath=wuppie -Lwuppie
dynX: $(DYNLIB) main.o
	mkdir wuppie
	mv $(DYNLIB) wuppie/.
	$(CC) $(LDFLAGS) -o $@ main.o $(LDLIBS)



## Erzeuge statische Bibliothek
$(STATLIB): $(OBJS)
	ar crv $@ $^


## Erzeuge dynamische Bibliothek
$(DYNLIB): $(OBJS)
	$(CC) -shared -o $@ $^



clean:
	rm -rf stat dyn dynX main *.o *.a *.so *~ wuppie/
