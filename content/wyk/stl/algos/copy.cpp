#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

struct starts_with {
    char c;
    starts_with(char c) : c{c} {}
    bool operator()(const std::string& name) {
        return name.length() > 0 && name[0] == c;
    }
};

int main() {
    std::array<std::string, 3> names = {"Alfred", "Batman", "Catwoman"};

    std::vector<std::string> vnames(names.size());
    std::copy(names.begin(), names.end(), vnames.begin());

    std::vector<std::string> good_names(names.size());
    auto it = std::copy_if(names.begin(), names.end(), good_names.begin(), starts_with('A'));
    good_names.erase(it, good_names.end());

    for (auto& name : good_names) {
        std::cout << name << "\n";
    }

    return 0;
}
