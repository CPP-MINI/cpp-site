CXX=g++
CXXFLAGS=-Wall -g
LDFLAGS=
AR=ar
ARFLAGS=rcs

.PHONY: all clean

all: l4_base32

l4_base32: main.o libbase32.a
	${CXX} ${LDFLAGS} $^ -o l4_base32

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

libbase32.a: encoder.o decoder.o
	${AR} ${ARFLAGS} libbase32.a $^

encoder.o: encoder.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

decoder.o: decoder.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@


clean:
	rm -f *.o *.a l4_base32