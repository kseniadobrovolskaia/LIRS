СXX?= g++
CXXFLAGS?= -Wall -std=c++2a -g


export CXX CXXFLAGS


.PHONY: clean

subsystem:
	cd Perfect_Cash && $(MAKE)
	cd LIRS && $(MAKE)
	cd LIRS_Test && $(MAKE)

clean:
	cd Perfect_Cash && $(MAKE) $@
	cd LIRS && $(MAKE) $@
	cd LIRS_Test && $(MAKE) $@


