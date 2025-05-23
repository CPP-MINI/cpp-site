CXX = g++
CXXFLAGS = -std=c++20 -Wall -fsanitize=address,leak -g
LDFLAGS = -fsanitize=address,leak

.PHONY: all clean

all: l6

l6: main.o Character.o
	${CXX} ${LDFLAGS} $^ -o $@

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

Character.o: Character.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f *.o l6
