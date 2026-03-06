#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i <= vec.size(); i++) {
        vec[i] = 2 * vec[i];
    }
    return 0;
}
