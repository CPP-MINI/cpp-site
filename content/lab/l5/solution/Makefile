CXX = g++
CXXFLAGS = -std=c++20 -Wall -fsanitize=address,leak -g
LDFLAGS = -fsanitize=address,leak

.PHONY: all clean

all: l5

l5: main.o MovieCollection.o
	${CXX} ${LDFLAGS} $^ -o $@

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

MovieCollection.o: MovieCollection.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f *.o L5
