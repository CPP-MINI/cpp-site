#include <iostream>
#include <vector>
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<unsigned int> v;
    for (size_t i = 0; i < 100'000'000; i++) {
        v.push_back(i);
    }
    unsigned int sum = 0;
    for (size_t i = 0; i < v.size(); i++) {
        sum += v[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

#ifdef NDEBUG
    std::cout << "release: " << sum << " (" << duration.count() << "us)" << std::endl;
#else
    std::cout << "debug: " << sum << " (" << duration.count() << "us)" << std::endl;
#endif
    return 0;
}