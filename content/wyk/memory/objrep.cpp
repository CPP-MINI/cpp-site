#include <iostream>
#include <iomanip>

int main() {
    int x = 12345; // jakiś obiekt

    unsigned char* bytes = reinterpret_cast<unsigned char*>(&x);

    for (std::size_t i = 0; i < sizeof(x); ++i) {
        std::cout << "Byte " << i << ": "
                  << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]) << "\n";
    }

    return 0;
}
