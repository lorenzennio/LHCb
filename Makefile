Target  = analyse

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

all:$(Target)

analyse: MyAnalysis.cpp
	g++ -o $@ MyAnalysis.cpp $(ROOTFLAGS) $(ROOTLIBS)

clean:
	$(RM) analyse
