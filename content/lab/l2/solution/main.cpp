#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>

#include "holey_string.hpp"
#include "memory_manipulation.hpp"
#include "vector3.hpp"

using namespace l2;

void print_readable_character(std::byte byte)
{
    if (byte >= std::byte{0x20} && byte <= std::byte{0x7E})
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
            std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(*(addr + idx))
                      << " ";
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

    vector3_mul(v1, 3);
    vector3_mul(v2, 5);
    vector3_mul(v3, 7);

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
            vector3_init(stack_array[i], static_cast<double>(i), static_cast<double>(i), static_cast<double>(i));
            std::cout << std::hex << &stack_array[0] << std::endl;
        }

        for (size_t i = 0; i < array_size; ++i)
            std::cout << vector3_length(stack_array[i]) << std::endl;

        dump_memory(reinterpret_cast<std::byte*>(stack_array), array_size * sizeof(Vector3));
    }

    // Heap
    {
        Vector3* heap_array = new Vector3[array_size];

        for (int i = 0; i < array_size; ++i)
        {
            vector3_init(heap_array[i], static_cast<double>(i), static_cast<double>(i), static_cast<double>(i));
            std::cout << std::hex << &heap_array[0] << std::endl;
        }

        for (int i = 0; i < array_size; ++i)
            std::cout << vector3_length(heap_array[i]) << std::endl;

        dump_memory(reinterpret_cast<std::byte*>(heap_array), array_size * sizeof(Vector3));
        delete[] heap_array;
    }

    // std::vector (wrapper for custom memory logic)
    {
        std::vector<Vector3> vectors_vector;

        for (int i = 0; i < array_size; ++i)
        {
            Vector3 temp;
            vector3_init(temp, i, i, i);
            vectors_vector.push_back(temp);
            std::cout << std::hex << &vectors_vector[0] << std::endl;  // Spooky things happening here...
        }

        for (int i = 0; i < vectors_vector.size(); ++i)
            std::cout << vector3_length(vectors_vector[i]) << std::endl;

        dump_memory(reinterpret_cast<std::byte*>(vectors_vector.data()), vectors_vector.size() * sizeof(Vector3));
    }

    std::cout << "STAGE 4" << std::endl;

    HoleyString hello;
    holey_string_assign(hello, "hello");

    holey_string_print(hello);
    std::cout << std::endl;
    dump_memory(reinterpret_cast<std::byte*>(&hello), sizeof(HoleyString));

    holey_string_hide(hello, "world");

    holey_string_print(hello);
    std::cout << std::endl;
    dump_memory(reinterpret_cast<std::byte*>(&hello), sizeof(HoleyString));

    std::cout << "STAGE 5" << std::endl;

    std::string sentence = "Hello world!";
    memcpy(reinterpret_cast<std::byte*>(sentence.data() + 6), reinterpret_cast<std::byte*>(sentence.data()), 5);
    std::cout << sentence << std::endl;

    std::string sentence2 = "Hello world once again!";
    memmove(reinterpret_cast<std::byte*>(sentence2.data() + 12), reinterpret_cast<std::byte*>(sentence2.data() + 6),
            10);
    std::cout << sentence2 << std::endl;

    return 0;
}
