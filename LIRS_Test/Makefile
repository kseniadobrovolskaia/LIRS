СXX?= g++
CXXFLAGS?= -Wall -std=c++2a -g
LDFLAGS=
SOURCES=LIRS_Test.cpp LIRS.hpp LIRS_Test.hpp Perfect_Cash.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=LIRS_Test.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -rf *.o *.exe