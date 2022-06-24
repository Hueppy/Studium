CFLAGS = -ansi -pedantic -Wall -I../../include
LDLIBS = -lwiringPi

TARGET = demo_ledanzeige

.PHONY: all
all: $(TARGET)

.PHONY: install
install: all
	mv $(TARGET) ../../bin/

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.~