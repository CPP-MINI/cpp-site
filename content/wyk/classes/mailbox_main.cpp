#include "mailbox.hpp"

#include <iostream>

int main() {
    Mailbox box;

    box.post("Hello, my name is Adam. Nice to meet You");
    box.post("Hey, wanna buy some crypto?");
    box.post("I'm looking for a good deal. Call me");

    while (!box.empty())
    {
        std::string msg = box.get();
        std::cout << "Received message: \"" << msg << "\"\n";
    }

    return 0;
}