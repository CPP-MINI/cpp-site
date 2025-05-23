CXX := g++
CXXFLAGS :=

ifdef EXTERN_POINTD
CXXFLAGS += -DEXTERN_POINTD
endif

all: main.out

main.o: main.cpp utils.hpp point.hpp
	$(CXX) -c $(CXXFLAGS) -o main.o main.cpp

utils.o: utils.cpp utils.hpp point.hpp
	$(CXX) -c $(CXXFLAGS) -o utils.o utils.cpp

main.out: main.o utils.o
	$(CXX) $(CXXFLAGS) -o main.out main.o utils.o

clean:
	rm -f main.out main.o utils.o
