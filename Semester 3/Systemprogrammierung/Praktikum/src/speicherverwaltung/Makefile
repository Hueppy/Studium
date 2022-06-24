CFLAGS = --std=c11 -pedantic -Wall -I../../include

TARGET = demo_speicherverwaltung

.PHONY: all
all: $(TARGET)

.PHONY: install
install: all
	mv $(TARGET) ../../bin/

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.~