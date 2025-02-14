#include "greeter.hpp"
#include "rome.hpp"

#include <iostream>

int main() {
    std::cout << greeter::greek() << std::endl;

    std::cout << "Creating provinces" << std::endl;

    rome::Province africa_proconsularis = rome::create_province("Africa Proconsularis");
    rome::add_city(&africa_proconsularis, "Carthago");
    rome::add_city(&africa_proconsularis, "Hadrumentum");

    rome::Province achaia = rome::create_province("Achaia");
    rome::add_city(&achaia, "Corinthus");
    rome::add_city(&achaia, "Athenæ");

    rome::Province aegyptus = rome::create_province("Ægyptus");
    rome::add_city(&aegyptus, "Alexandira");
    rome::add_city(&aegyptus, "Ptolemais");

    std::cout << "Printing provinces" << std::endl;
    std::cout << rome::description(&africa_proconsularis) << std::endl;
    std::cout << rome::description(&achaia) << std::endl;
    std::cout << rome::description(&aegyptus) << std::endl;
}
