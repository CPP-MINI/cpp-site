CXX=g++
CXXFLAGS=-Wall -fsanitize=address,leak
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l2

# $^ - this variable holds all dependencies of given target
l2: vector3.o main.o holey_string.o memory_manipulation.o
	${CXX} ${LDFLAGS} $^ -o l2 

# $< - this variable holds only first dependency of given target
# $@ - this variables holds the target itself
main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

vector3.o: vector3.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

holey_string.o: holey_string.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

memory_manipulation.o: memory_manipulation.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@


clean:
	rm -f *.o l2
