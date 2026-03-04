CXX = g++
.PHONY : all clean

all : pager

pager : pager.cpp bounded_buffer.cpp bounded_buffer.hpp
	${CXX} -o pager bounded_buffer.cpp pager.cpp

clean :
	rm -f pager
