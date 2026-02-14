#include "bounded_buffer.hpp"

#include <iostream>

int buffer_size(const bounded_buffer* buffer){
    return buffer->buffer.size();
}

int buffer_capacity(const bounded_buffer* buffer){
    return buffer->capacity;
}

void flush_buffer(bounded_buffer* buffer){
    for (const auto& l : buffer->buffer)
        std::cout << l << std::endl;
    std::cout << "=====" << std::endl;
    buffer->buffer.clear();
}

bool add_to_buffer(bounded_buffer* buffer, std::string line){
    if (buffer_size(buffer) == buffer_capacity(buffer))
        return false;

    buffer->buffer.push_back(line);
    return true;
}
