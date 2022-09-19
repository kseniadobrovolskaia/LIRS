
CC=g++
CFLAGS=-c -Wall -std=c++20 
LDFLAGS=
SOURCES=LIRS.cpp LIRS.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=LIRS

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


