#include <iostream>
#include <vector>
#include <algorithm>

bool is_even(int i) {
    return i % 2 == 0;
}

int main() {
    std::vector<int> values = {4, 2, 5, 1, 10, 4, 24, 17};
    auto rit = std::remove_if(values.begin(), values.end(), is_even);
    for (auto it = values.begin(); it != rit; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    values.erase(rit, values.end());
    return 0;
}
