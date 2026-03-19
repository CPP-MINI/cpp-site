#include <iostream>
#include <vector>

int main() {
    int capacity ;
    std::vector<std::string> names;

    std::cout << "< Podaj liczbę użytkowników:" << std::endl;
    std::cout << "> ";
    std::cin >> capacity;
    for (int i = 0; i < capacity; i++) {
        std::cout << "< Podaj pseudonim:" << std::endl;
        std::cout << "> ";
        std::string name;
        std::cin >> name;
        names.push_back(name);
        std::cout << "< Witaj, " << name << "!" << std::endl;
        std::cout << "< Użytkownicy: " << names.size() << "/" << capacity << std::endl;
        for (int j = 0; j < names.size(); j++)
            std::cout << "\t- " << names[j] << std::endl;
    }
}
