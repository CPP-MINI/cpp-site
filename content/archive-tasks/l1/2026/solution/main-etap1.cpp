#include <iostream>
#include <vector>

int main() {
    std::cout << "< Podaj pseudonim:" << std::endl;
    std::cout << "> ";
    std::string name;
    std::cin >> name;
    std::cout << "< Witaj, " << name << "!" << std::endl;
}
