#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <vector>

#include "vector3.h"
#include "holey_string.h"
#include "memory_manipulation.h"

using namespace l2;

void print_readable_character(std::byte byte)
{
    if (byte >= std::byte{0x20} and byte <= std::byte{0x7E})
        std::cout << static_cast<char>(byte);
    else
        std::cout << ".";  // Non readable character cannot be shown in the console
}

void dump_memory(std::byte* start, size_t count)
{
    const long int window_width = 8;

    // Aliasing rules are ok here. size_t is the same size as any pointer.
    const std::byte* finish_addr = start + count;
    for (std::byte* addr = start; addr < finish_addr; addr += window_width)
    {
        int max_idx = std::min(finish_addr - addr, window_width);
        std::cout << std::hex << addr << ": ";
        for (int idx = 0; idx < max_idx; ++idx)
            std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(*(addr + idx)) << " ";
        std::cout << "| ";
        for (int idx = 0; idx < max_idx; ++idx)
            print_readable_character(*(addr + idx));
        std::cout << " |" << std::endl;
    }
}

int main()
{
    std::cout << "STAGE 1" << std::endl;
    // ETAP 1
    Vector3 v1 = BaseVector1;
    Vector3 v2 = BaseVector2;
    Vector3 v3 = BaseVector3;

    v1.mul(3);
    v2.mul(5);
    v3.mul(7);

    Vector3 result_vector = vector3_add(v1, vector3_add(v2, v3));
    vector3_print(result_vector);

    dump_memory(reinterpret_cast<std::byte*>(&v1), sizeof(Vector3));
    
    std::cout << "STAGE 2 and 3" << std::endl;

    const int array_size = 10;
    // Stack
    {
        Vector3 stack_array[array_size];

        for (int i = 0; i < array_size; ++i)
        {
            stack_array[i] = {static_cast<double>(i), static_cast<double>(i), static_cast<double>(i)};
            std::cout << std::hex << &stack_array[0] << std::endl;
        }

        for (const Vector3& v : stack_array)
            std::cout << v.length() << std::endl;

        dump_memory(reinterpret_cast<std::byte*>(stack_array), array_size * sizeof(Vector3));
    }

    // Heap
    {
        Vector3* heap_array = new Vector3[array_size];

        for (int i = 0; i < array_size; ++i)
        {
            heap_array[i] = {static_cast<double>(i), static_cast<double>(i), static_cast<double>(i)};
            std::cout << std::hex << &heap_array[0] << std::endl;
        }

        for (int i = 0; i < array_size; ++i)
            std::cout << heap_array[i].length() << std::endl;

        dump_memory(reinterpret_cast<std::byte*>(heap_array), array_size * sizeof(Vector3));
        delete[] heap_array;
    }

    // std::vector (wrapper for custom memory logic)
    {
        std::vector<Vector3> vectors_vector;

        for (int i = 0; i < array_size; ++i)
        {
            vectors_vector.emplace_back(i, i, i);
            std::cout << std::hex << &vectors_vector[0] << std::endl;  // Spooky things happening here...
        }

        for (const Vector3& v : vectors_vector)
            std::cout << v.length() << std::endl;

        dump_memory(reinterpret_cast<std::byte*>(vectors_vector.data()), vectors_vector.size() * sizeof(Vector3));
    }

    std::cout << "STAGE 4" << std::endl;
    
    HoleyString hello;
    hello.assign("hello");

    hello.print();
    std::cout << std::endl;
    dump_memory(reinterpret_cast<std::byte*>(&hello), sizeof(HoleyString));

    hello.hide("world");
    
    hello.print();
    std::cout << std::endl;
    dump_memory(reinterpret_cast<std::byte*>(&hello), sizeof(HoleyString));
    
    std::cout << "STAGE 5" << std::endl;
    
    std::string sentence = "Hello world!";
    memcpy(reinterpret_cast<std::byte*>(sentence.data() + 6), reinterpret_cast<std::byte*>(sentence.data()), 5);
    std::cout << sentence << std::endl;

    std::string sentence2 = "Hello world once again!";
    memmove(reinterpret_cast<std::byte*>(sentence2.data() + 12), reinterpret_cast<std::byte*>(sentence2.data() + 6), 10);
    std::cout << sentence2 << std::endl;

    return 0;
}
