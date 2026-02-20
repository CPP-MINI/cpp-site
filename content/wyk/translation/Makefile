all: prog.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

helper.o: helper.cpp
	g++ -c helper.cpp -o helper.o

prog.exe: main.o helper.o
	g++ main.o helper.o -o prog.exe
