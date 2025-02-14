COMPILER=g++

.PHONY: all
all: program_1 program_2

# Program 1
program_1: program_1.o vars.o libgreeter.a
	${COMPILER} vars.o program_1.o -L. -lgreeter -o program_1

program_1.o: program_1.cpp
	${COMPILER} -c program_1.cpp -o program_1.o

vars.o: vars.cpp
	${COMPILER} -c vars.cpp -o vars.o

# Program 2
program_2: program_2.o libgreeter.a librome.so
	${COMPILER} program_2.o -L. -lgreeter -lrome -o program_2

# Greeter static library
greeter.o: greeter.cpp
	${COMPILER} -c greeter.cpp -o greeter.o

libgreeter.a: greeter.o
	ar rcs libgreeter.a greeter.o

# Rome dynamic library
rome.o: rome.cpp
	${COMPILER} -c -fPIC rome.cpp -o rome.o

librome.so: rome.o
	${COMPILER} -shared rome.o -o librome.so

.PHONY: clean
clean:
	rm -rf program_1 program_1.o vars.o
	rm -rf program_2 program_2.o
	rm -rf greeter.o libgreeter.a
	rm -rf rome.o librome.so
