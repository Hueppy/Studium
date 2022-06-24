COMMONFLAGS = -pedantic -Wall -g -I../../include
CFLAGS = --std=c11 $(COMMONFLAGS)
CXXFLAGS = --std=c++14 $(COMMONFLAGS)
OBJS := RefCounter.o demo_SmartPointer.o
TARGET = demo_SmartPointer

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
