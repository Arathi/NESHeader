CC = gcc
CXX = g++
CFLAGS = 
CXXFLAGS = -Wall -g

all: Main.o
	$(CXX) Main.o -o nesheader $(CFLAGS) $(CXXFLAGS)
	
Main.o: Main.cxx
	$(CXX) Main.cxx -c -o Main.o $(CFLAGS) $(CXXFLAGS)

clean:
	rm -f *.o nesheader
