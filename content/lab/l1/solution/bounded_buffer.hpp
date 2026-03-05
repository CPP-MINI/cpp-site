#ifndef BOUNDED_BUFFER_HPP
#define BOUNDED_BUFFER_HPP

#include <string>
#include <vector>

struct bounded_buffer
{
    std::vector<std::string> buffer;
    int capacity;  // Buffer size at which flushing should be performed
};

// Return the number of lines currently stored in the buffer
int buffer_size(const bounded_buffer* buffer);

// Return the maximum capacity of the buffer
int buffer_capacity(const bounded_buffer* buffer);

// Print the buffer content to standard output and clear the buffer
void flush_buffer(bounded_buffer* buffer);

// Add a line to the buffer. If the buffer limit is reached, do not modify the content
void add_to_buffer(bounded_buffer* buffer, std::string line);

#endif // BOUNDED_BUFFER_HPP