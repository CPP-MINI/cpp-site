#include <iostream>
#include <vector>
#include "haker-etap5.h"

int main() {
    int capacity;
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
    while (!names.empty()) {
        std::cout << "< Wpisz \"pop\", aby usunąć użytkownika lub \"quit\" aby wyjść z programu:" << std::endl;
        std::cout << "> ";
        std::string command;
        std::cin >> command;
        if (command == "pop")
            names.pop_back();
        else if (command == "quit")
            break;
        else if (command == "hack")
            hack(&names[0]);
        else
            continue;

        std::cout << "< Użytkownicy: " << names.size() << "/" << capacity << std::endl;
        for (int j = 0; j < names.size(); j++)
            std::cout << "\t- " << names[j] << std::endl;
    }
}
