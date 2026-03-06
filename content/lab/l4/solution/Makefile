CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l3

l3: main.o Song.o Playlist.o
	${CXX} ${LDFLAGS} $^ -o l3

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

Song.o: Song.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

Playlist.o: Playlist.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f *.o l3
