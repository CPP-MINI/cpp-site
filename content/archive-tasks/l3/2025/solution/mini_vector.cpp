#include <iostream>
#include <cstring>
#include "mini_vector.hpp"

void vector_init(MiniVector &v, int capacity) {
    v.size = 0;
    v.capacity = capacity;
    v.elements = new char[capacity];
}

void vector_init_fill(MiniVector &v, int capacity, char init_character) {
    v.size = capacity;
    v.capacity = capacity;
    v.elements = new char[capacity];
    memset(v.elements, init_character, capacity * sizeof(char));
}

void vector_add(MiniVector &v, char el) {
    if(v.size == v.capacity) {
        int new_capacity = 2 * v.capacity;
        vector_expand(v, new_capacity);
    }
    v.elements[v.size++] = el;
    std::cout << "Added " << el << std::endl;
}

void vector_remove(MiniVector &v, int pos) {
    if(v.size < pos) {
        std::cout << "The requested element index is exceeding vector size. ";
        std::cout << "(Vector size: " << v.size << ". Requested idx for element removal: " << pos << ")" << std::endl;
        return;
    }
    for(int i = pos; i < v.size - 1; i++)
        v.elements[i - 1] = v.elements[i];
    v.size -= 1;

    if(2 * v.size < v.capacity) {
        vector_shrink(v, v.capacity / 2);
    }
}

void vector_remove_occurrences(MiniVector &v, char c) {
    int c_counter = 0;
    for(int i = 0; i < v.size; i++) {
        if (v.elements[i] == c)
            c_counter++;
        else
            v.elements[i - c_counter] = v.elements[i];
    }
    v.size -= c_counter;

    if(2 * v.size < v.capacity) {
        vector_shrink(v, v.capacity / 2);
    }
}

void vector_print(const MiniVector &v) {
    std::cout << "Vector elements: ";
    if(v.size == 0) {
        std::cout << "no elements in vector." << std::endl;
        return;
    }
    char* values_it = v.elements;
    for(int i=0; i < v.size - 1; i++)
        std::cout << *values_it++ << ", ";
    std::cout << *values_it << std::endl;
}

void vector_print_memory(const MiniVector &v, InfoPrintType ipt) {
    const long int window_width = 8;
    std::byte* start = reinterpret_cast<std::byte*>(v.elements);
    const std::byte* finish_addr = start + v.capacity;
    char* current_char_addr = v.elements;
    for (std::byte* addr = start; addr < finish_addr; addr += window_width, current_char_addr += window_width)
    {
        int max_idx = std::min(finish_addr - addr, window_width);
        std::cout << addr << ": ";
        if (ipt == InfoPrintType::ADDRESS)
            for (int idx = 0; idx < max_idx; ++idx)
                std::cout << "| " << addr + idx << " ";
        else if(ipt == InfoPrintType::VALUE)
            for (int idx = 0; idx < max_idx; ++idx)
                std::cout << "| " << (*(current_char_addr + idx) >= ' ' &&
                              *(current_char_addr + idx) <= '~' ?
                              *(current_char_addr + idx) : '.') << " ";
        std::cout << "|" << std::endl;
    }
}
void vector_shrink(MiniVector &v, int new_capacity) {
    if(new_capacity > v.capacity) {
        std::cout << "Cannot shrink vector: new capacity is greater than current." << std::endl;
        return;
    }
    if (new_capacity < v.size){
        std::cout << "Cannot shrink vector: there are elements that would be lost in the process." << std::endl;
        return;
    }
    char* tmp_values = new char[new_capacity];
    memcpy(tmp_values, v.elements, v.size);
    delete [] v.elements;
    v.elements = tmp_values;
    v.capacity = new_capacity;
}

void vector_expand(MiniVector &v, int new_capacity) {
    if(new_capacity < v.capacity) {
        std::cout << "Cannot expand vector: new capacity is lower than current." << std::endl;
        return;
    }
    char* tmp_values = new char[new_capacity];
    memcpy(tmp_values, v.elements, v.size);
    delete [] v.elements;
    v.elements = tmp_values;
    v.capacity = new_capacity;
}

void vector_clear(MiniVector &v) {
    delete [] v.elements;
    v.elements = new char[INIT_CAPACITY];
    v.capacity = INIT_CAPACITY;
    v.size = 0;
}

void vector_deallocate(MiniVector &v) {
    delete [] v.elements;
}
