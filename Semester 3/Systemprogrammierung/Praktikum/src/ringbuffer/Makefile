COMMONFLAGS = -pedantic -Wall -g -I../../include -DMALLOC
CFLAGS = --std=c11 $(COMMONFLAGS)
CXXFLAGS = --std=c++14 $(COMMONFLAGS)
OBJS := speicherverwaltung.o demo_RingBuffer.cpp
TARGET = demo_RingBuffer

$(TARGET): $(OBJS)

speicherverwaltung.o: ../speicherverwaltung/speicherverwaltung.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all
all: $(TARGET)

.PHONY: install
install: all
	mv $(TARGET) ../../bin/

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.~
