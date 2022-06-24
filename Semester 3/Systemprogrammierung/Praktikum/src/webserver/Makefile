COMMONFLAGS = -pedantic -Wall -g -I../../include
CFLAGS = --std=c11 $(COMMONFLAGS)
CXXFLAGS = --std=c++14 $(COMMONFLAGS)
OBJS := fbtHttpd.o
TARGET = fbtHttpd

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

.PHONY: all
all: $(TARGET)

.PHONY: install
install: all
	mv $(TARGET) ../../bin/

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.~
