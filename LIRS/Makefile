СXX?= g++
CXXFLAGS?= -Wall -std=c++2a -g
LDFLAGS=
SOURCES= LIRS.cpp LIRS.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=LIRS.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -rf *.o *.exe