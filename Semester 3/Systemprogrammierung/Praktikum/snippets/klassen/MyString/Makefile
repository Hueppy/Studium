##
## Makefile
##
## Author: Carsten Gips
##

CXX=g++

CXXFLAGS=-std=c++14 -pedantic -Wall -Werror
CXXFLAGS+=-I$(INCLUDE)

LDFLAGS=-L$(LIB)
LDLIBS=-lm -lstdc++


INCLUDE=.
LIB=.

SRC  = main.cpp MyString.cpp
OBJ  = $(SRC:.cpp=.o)
PROG = MyString


.PHONY: all
all: $(PROG)
	./$<

$(PROG): $(OBJ)


.PHONY: clean
clean:
	rm -rf *.o $(PROG)
