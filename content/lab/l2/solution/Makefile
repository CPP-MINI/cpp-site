CXX=g++
CXXFLAGS=-Wall -fsanitize=address,leak
LDFLAGS=-fsanitize=address,leak

PHONY: all clean

all: l2

l2: vector3.o main.o
	${CXX} ${LDFLAGS} $^ -o l2 

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

vector3.o: vector3.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f vector3.o main.o
	rm -f l2
