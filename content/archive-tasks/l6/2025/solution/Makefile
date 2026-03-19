CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l6

l6: main.o Cargoes.o TransportVessels.o LogisticsReport.o
	${CXX} ${LDFLAGS} main.o Cargoes.o TransportVessels.o LogisticsReport.o -o l6

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

Cargoes.o: Cargoes.cpp
	${CXX} ${CXXFLAGS} -c Cargoes.cpp -o Cargoes.o

TransportVessels.o: TransportVessels.cpp
	${CXX} ${CXXFLAGS} -c TransportVessels.cpp -o TransportVessels.o

LogisticsReport.o: LogisticsReport.cpp
	${CXX} ${CXXFLAGS} -c LogisticsReport.cpp -o LogisticsReport.o

clean:
	rm -f *.o l6
