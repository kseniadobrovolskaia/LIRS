СXX?= g++
CXXFLAGS?= -Wall -std=c++2a -g
LDFLAGS=
SOURCES= Perfect_Cash.cpp Perfect_Cash.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Perfect_Cash.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -rf *.o *.exe