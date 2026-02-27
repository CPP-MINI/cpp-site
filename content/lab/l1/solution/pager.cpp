#include <iostream>
#include <string>
#include <vector>

#include "bounded_buffer.hpp"

#include "bounded_buffer.hpp"

#define PAGE_SIZE 4

int main() {

    bounded_buffer buffer;
    buffer.capacity = PAGE_SIZE;

    std::string line;
    while (std::getline(std::cin, line)) {
        add_to_buffer(&buffer, line);
    
        if (buffer_size(&buffer) == buffer_capacity(&buffer)){
            flush_buffer(&buffer);
        }
    }

    if (buffer_size(&buffer) > 0)
        flush_buffer(&buffer);

    return 0;
}