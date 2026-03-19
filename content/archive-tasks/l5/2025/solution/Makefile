CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l5

l5: main.o SensorCollection.o
	${CXX} ${LDFLAGS} main.o SensorCollection.o -o l5

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

SensorCollection.o: SensorCollection.cpp
	${CXX} ${CXXFLAGS} -c SensorCollection.cpp -o SensorCollection.o

clean:
	rm -f *.o l5
