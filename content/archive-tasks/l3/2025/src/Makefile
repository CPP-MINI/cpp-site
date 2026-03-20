COMPILER=g++

.PHONY: all
all: main_program

# Main program
main_program: main_program.o
	${COMPILER} -g -fsanitize=address main_program.o -o main_program

main_program.o: main.cpp
	${COMPILER} -c main.cpp -o main_program.o

.PHONY: clean
clean:
	rm -f main_program.o main_program