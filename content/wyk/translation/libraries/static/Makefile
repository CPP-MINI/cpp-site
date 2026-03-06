all: my_executable

my_executable: main.o helper.o libexternal_library.a
	g++ main.o helper.o -L. -lexternal_library -o my_executable

main.o: main.cpp
	g++ -c main.cpp -o main.o

helper.o: helper.cpp
	g++ -c helper.cpp -o helper.o

libexternal_library.a: file1.o file2.o
	ar rcs libexternal_library.a file1.o file2.o

file1.o: file1.cpp
	g++ -c file1.cpp -o file1.o

file2.o: file2.cpp
	g++ -c file2.cpp -o file2.o
