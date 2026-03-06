#include <cstddef>

class Dummy {
    int i;
public:
    Dummy(int i) : i(i) {}
};

int main() {
    size_t n = 3;
    Dummy** tab = new Dummy*[n];
    for (size_t i = 0; i < 3; ++i) {
       tab[i] = new Dummy(i);
    }
    delete[] tab;
    return 0;
}
