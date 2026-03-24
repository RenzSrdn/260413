# Makefile per il progetto Stack<T>

CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11 -g
TARGET = main.exe
SRCS = main.cpp
HDRS = stack.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.txt

valgrind: $(TARGET)
	valgrind --leak-check=full --error-exitcode=1 ./$(TARGET)

.PHONY: all clean valgrind