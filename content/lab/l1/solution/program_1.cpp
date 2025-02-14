#include <iostream>

#include "greeter.hpp"
#include "vars.hpp"

int main() {
    std::cout << greeter::english() << std::endl;
    std::cout << greeter::polish() << std::endl;
    std::cout << greeter::greek() << std::endl;

    print_vars();
    inc_vars();
    print_vars();
    std::cout << "global_extern from program_1: " << global_extern << std::endl;
}
