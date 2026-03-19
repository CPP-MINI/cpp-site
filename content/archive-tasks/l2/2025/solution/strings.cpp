#include "strings.hpp"

namespace strings {
    int COMBINE_COUNT = 0;

    std::string combine_strings(std::string s1, std::string s2) {
        COMBINE_COUNT += 1;
        return s1 + " " + s2;
    }
}
