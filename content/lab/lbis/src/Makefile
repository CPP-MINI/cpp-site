CXX=g++
CXXFLAGS=-Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak
AR=ar
ARFLAGS=rcs

.PHONY: all clean

all: lbis_base32

lbis_base32: main.o libbase32.a
	${CXX} ${LDFLAGS} $^ -o lbis_base32

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

libbase32.a: encoder.o decoder.o
	${AR} ${ARFLAGS} libbase32.a $^

encoder.o: encoder.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

decoder.o: decoder.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@


clean:
	rm -f *.o *.a lbis_base32