# Makefile for the socket programming example
#
STD_FLAGS = -W -Wall -ansi -pedantic

CPPSOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)

all: $(CPPSOURCES)

%.cpp: $(CPPSOURCES: .cpp= .o) $(HEADERS)
	g++ $(CPPSOURCES) $< -c -I./include

%.o: %.cpp $(HEADERS)
	g++ $(STD_FLAGS) -c $< -I./include

clean:
	rm -f *.o 