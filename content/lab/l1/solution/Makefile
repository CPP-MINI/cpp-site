CXX=g++

.PHONY: all clean

all: pager

pager: pager.cpp bounded_buffer.cpp
	${CXX} -o pager bounded_buffer.cpp pager.cpp

clean:
	rm -f pager
