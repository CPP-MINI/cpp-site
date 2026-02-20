my.exe: main.o math.o
	clang++ -std=c++20 -fprebuilt-module-path=. main.o math.o -o my.exe

math.pcm: math.cppm
	clang++ -std=c++20 --precompile math.cppm -o math.pcm

math.o: math.pcm
	clang++ -c math.pcm -o math.o

main.o: main.cpp math.pcm
	clang++ -std=c++20 -fprebuilt-module-path=. -c main.cpp -o main.o

clean:
	rm -f *.o *.pcm my.exe