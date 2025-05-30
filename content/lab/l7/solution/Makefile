CXX = g++
CXXFLAGS = -std=c++20 -Wall -fsanitize=address,leak -g
LDFLAGS = -fsanitize=address,leak

.PHONY: all clean

all: l7

l7: main.o
	${CXX} ${LDFLAGS} $^ -o $@

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f *.o l7
