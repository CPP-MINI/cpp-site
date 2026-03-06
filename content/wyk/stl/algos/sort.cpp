#include <iostream>
#include <array>
#include <algorithm>

struct person {
    std::string name;
    std::string surname;

    person(const std::string& n, const std::string& s) : name(n), surname(s) {}
};

struct person_cmp {
    bool operator()(const person& p1, const person& p2) {
        return p1.surname == p2.surname ? p1.name < p2.name : p1.surname < p2.surname;
    }
};

int main() {
    std::array<person, 5> ppl = {
        person{"John", "Doe"},
        person{"Jane", "Bluford"},
        person{"Joseph", "Doe"},
        person{"Jac", "Bluford"},
        person{"Jessica", "Bluford"}
    };
    std::sort(ppl.begin(), ppl.end(), person_cmp{});
    for (auto& p : ppl) {
        std::cout << p.name << " " << p.surname << "\n";
    }
    return 0;
}
