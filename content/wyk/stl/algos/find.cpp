#include <iostream>
#include <vector>
#include <algorithm>

bool is_short(const std::string& name) {
    return name.length() < 4;
}

int main() {
    std::vector<std::string> names = {
        "John", "Jane", "Joseph", "Jac", "Jessica", "Jose", "Josh"
    };

    auto joseph = std::find(names.begin(), names.end(), "Joseph");
    std::cout << "Joseph = " << *joseph << "\n";

    auto s = std::find_if(names.begin(), names.end(), is_short);
    std::cout << "Short = " << *s << "\n";

    return 0;
}
