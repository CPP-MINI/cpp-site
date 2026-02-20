#include <iostream>
#include <vector>
#include <numeric>

int sum_agg(int acc, int val) {
    return acc + val;
}

int prod_agg(int acc, int val) {
    return acc * val;
}

std::string cat_agg(std::string acc, int val) {
    return acc + std::to_string(val) + ",";
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int sum = std::accumulate(nums.begin(), nums.end(), 0, sum_agg);
    std::cout << "Sum: " << sum << "\n";
    int prod = std::accumulate(nums.begin(), nums.end(), 1, prod_agg);
    std::cout << "Prod: " << prod << "\n";
    std::string cat = std::accumulate(nums.begin(), nums.end(), std::string{}, cat_agg);
    std::cout << "Cat: " << cat << "\n";
    return 0;
}
