#include <iostream>

#include "helper.hpp"
#include "external.hpp"

int main() {
    std::cout << "helper = " << helper << std::endl;
    external::foo();
    // external::goo();
    return 0;
}
