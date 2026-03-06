CXX := g++
CXXFLAGS :=

all: main.out

main.o: main.cpp rectangle.hpp point.hpp
	$(CXX) -c $(CXXFLAGS) -o main.o main.cpp

rectangle.o: rectangle.cpp rectangle.hpp point.hpp
	$(CXX) -c $(CXXFLAGS) -o rectangle.o rectangle.cpp

main.out: main.o rectangle.o
	$(CXX) $(CXXFLAGS) -o main.out main.o rectangle.o

clean:
	rm -f main.out main.o rectangle.o
