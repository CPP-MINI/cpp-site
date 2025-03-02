CXX=gcc
CXXFLAGS=-Wall -fsanitize=address
LDFLAGS=-fsanitize=address

PHONY: all clean

all: vector3.o
	echo "build a binary here"

vector3.o: vector3.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f vector3.o
