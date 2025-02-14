#include "vars.hpp"

#include <iostream>

int global_extern = 0;
static int global_static = 0;

void inc_vars() {
    std::cout << "Increasing..." << std::endl;
    global_extern += 1;
    global_static += 1;
}

void print_vars() {
    std::cout << "global_extern: " << global_extern << std::endl;
    std::cout << "global_static: " << global_static << std::endl;
}
