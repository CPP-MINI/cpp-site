all: my.exe

my.exe: main.o helper.o libexternal_library.so
	g++ main.o helper.o -L. -lexternal_library -o my.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

helper.o: helper.cpp
	g++ -c helper.cpp -o helper.o

libexternal_library.so: file1.o file2.o
	g++ -shared -o libexternal_library.so file1.o file2.o

file1.o: file1.cpp
	g++ -c -fPIC file1.cpp -o file1.o

file2.o: file2.cpp
	g++ -c -fPIC file2.cpp -o file2.o
