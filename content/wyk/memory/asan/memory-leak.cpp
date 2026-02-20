#include <cstddef>

int main() {
    const std::size_t size = 128;
    auto arr = new int*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new int{i};
    }
    int sum = 0;
    for (std::size_t i = 0; i < size; i++) {
        sum += *arr[i];
    }
    delete[] arr;
    return 0;
}
