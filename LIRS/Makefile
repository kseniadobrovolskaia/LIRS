CXX?=g++
CXXFLAGS?=-Wall -std=c++2a
LDFLAGS=
SOURCES= LIRS.h LIRS.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=LIRS.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -rf *.o *.exe