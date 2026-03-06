all: my.exe

my.exe: main.o lib1.a lib2.a
	#g++ -L. -l1 -l2 main.o -o my.exe # undefined
	#g++ main.o -L. -l2 -l1 -o my.exe # undefined
	g++ main.o -L. -l1 -l2 -o my.exe # ok

main.o: main.cpp
	g++ -c main.cpp -o main.o

lib1.a: lib1.o
	ar rcs lib1.a lib1.o

lib2.a: lib2.o
	ar rcs lib2.a lib2.o

lib1.o: lib1.cpp
	g++ -c lib1.cpp -o lib1.o

lib2.o: lib2.cpp
	g++ -c lib2.cpp -o lib2.o

clean:
	rm -f lib1.o lib2.o main.o lib2.a lib1.a my.exe
