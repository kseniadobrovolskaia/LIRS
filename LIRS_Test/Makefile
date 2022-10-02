
CC=g++
CFLAGS=-c -Wall -std=c++20 
LDFLAGS=
SOURCES=LIRS_Test.cpp LIRS.cpp LIRS.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=LIRS_Test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


