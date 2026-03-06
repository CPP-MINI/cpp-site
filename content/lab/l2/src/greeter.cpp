#include "greeter.hpp"

namespace greeter {
    std::string english() { return "Hello world!"; }

    std::string polish() {
        // Unlike on Windows, usually there are no problems with including special characters in strings on UNIX
        // systems.
        return "Witaj świecie!";
    }

    std::string greek() {
        // Same with different alphabeds (e.g. Greek).
        return "Χαῖρε κόσμε!";
    }
}
