#include <vector>
#include <stdexcept>
#include <iostream>

int divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

std::vector<int> do_divisions(std::vector<std::pair<int, int>> fractions) {
    std::vector<int> results;
    for (auto [n, d] : fractions) {
        std::cout << "Dividing " << n << " by " << d << "\n";
        results.push_back(divide(n, d));
    }
    return results;
}

int main() {
    try {
        do_divisions({ {1, 1}, {2, 1}, {3, 2}, {4, 0}, {2, 2} });
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
    return 0;
}
