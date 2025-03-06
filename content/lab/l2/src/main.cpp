#include <iostream>


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

    // STAGE 3: Implement me!
    // Hint: you can use print_readable_character function to print arbitrary byte as character
}

int main()
{
    std::cout << "STAGE 1" << std::endl;

    // STAGE 1: instatiate a Vector3 here
    
    std::cout << "STAGE 2 and 3" << std::endl;

    const int array_size = 10;
    // STAGE 2: stack, heap and std::vector

    
    std::cout << "STAGE 4" << std::endl;
    
    // STAGE 4: HoleyString should be created here
    
    std::cout << "STAGE 5" << std::endl;
    
    // STAGE 5: test your memcpy and memmove implementations here

    return 0;
}
