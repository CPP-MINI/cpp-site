CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l3

l3: main.o Subtask.o Task.o
	${CXX} ${LDFLAGS} $^ -o l3

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

Subtask.o: Subtask.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

Task.o: Task.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f *.o l3
