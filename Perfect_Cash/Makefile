
CC=g++
CFLAGS=-c -Wall -std=c++20 
LDFLAGS=
SOURCES=Perfect_Cash.cpp Perfect_Cash.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Perfect_Cash

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


