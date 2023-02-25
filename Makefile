CXX=g++
INCDIR=
LIBDIR=
CXXFLAGS=-g -Wall -ansi -pedantic

MAIN=main
OJBECTS=$(patsubst %.cpp,%.o,$(wildcard *.cpp)) $(patsubst %.cxx,%.o,$(wildcard *.cxx))

.PHONY: rcs clean tags

$(MAIN): $(OJBECTS)
	$(CXX) $(LIBDIR) -o $@ $^

ifeq ($(wildcard depMakefile),depMakefile)
include ./depMakefile
endif

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $< -o $@

%.o : %.cxx
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $< -o $@

CSOURCES=$(wildcard *.cxx *.cpp)
HSOURCES=$(wildcard *.h *.hpp *.hxx)
SOURCES=$(CSOURCES) $(HSOURCES)
dep:
	@ $(CXX) -MM $(CSOURCES) $(INCDIR) > depMakefile

clean:
	rm -f $(OJBECTS)
	rm -f $(MAIN)
	rm -f $(basename $(wildcard *.cpp *.cxx))
	rm -f $(basename $(wildcard *.o))
	rm -f $(wildcard *.o)
	clean.sh

tags:
	etags $(SOURCES)

.PHONY: rcs
rcs:
	@ for FILE in $(SOURCES); \
	do \
		ci -l $$FILE; \
	done
