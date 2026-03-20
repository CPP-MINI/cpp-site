COMPILER=g++

.PHONY: all
all: test main_program

# Test program
test: test.o liboperations.a
	${COMPILER} test.o -L. -loperations -o test

test.o: test.cpp
	${COMPILER} -c test.cpp -o test.o

# Main program
main_program: main_program.o libhello.so
	${COMPILER} main_program.o -L. -lhello -o main_program

main_program.o: main_program.cpp
	${COMPILER} -c main_program.cpp -o main_program.o

# Operations static library
vectors.o: vectors.cpp
	${COMPILER} -c vectors.cpp -o vectors.o

strings.o: strings.cpp
	${COMPILER} -c strings.cpp -o strings.o

liboperations.a: strings.o vectors.o
	ar rcs liboperations.a strings.o vectors.o

# Hello shared library
hello.o: hello.cpp
	${COMPILER} -c -fPIC hello.cpp -o hello.o

libhello.so: hello.o
	${COMPILER} -shared hello.o -o libhello.so

.PHONY: clean
clean:
	rm -f test test.o
	rm -f main_program.o main_program
	rm -f liboperations.a vectors.o strings.o
	rm -f libhello.so hello.o
