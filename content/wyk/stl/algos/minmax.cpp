#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {4, 2, 5, 3};
    auto min = std::min_element(v.begin(), v.end());
    auto max = std::max_element(v.begin(), v.end());
    std::cout << "Min: " << *min << "\n";
    std::cout << "Max: " << *max << "\n";

    std::cout << "min(3,5) = " << std::min(3, 5) << std::endl;
    std::cout << "max(3,5) = " << std::max(3, 5) << std::endl;
    std::cout << "clamp(3,5,10) = " << std::clamp(3, 5, 10) << "\n";
    return 0;
}
