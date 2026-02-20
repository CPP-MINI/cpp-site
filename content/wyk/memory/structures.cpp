#include <cstddef>
#include <iostream>
#include <iomanip>

struct S {
  char c;
  int x;
};

int main() {
    S s = {'a', 3};
    static_assert(sizeof(S) == 8, "surprise!");
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&s);

    for (std::size_t i = 0; i < sizeof(s); ++i) {
        std::cout << "Byte " << i << ": "
                  << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]) << "\n";
    }

    S copy = s;
    std::cout << copy.c << " " << copy.x << "\n";
    return 0;
}
