#include <memory>

std::unique_ptr<int> process(std::unique_ptr<int> ptr)
{
    *ptr *= 2;
    return ptr;
}

void process(int* ptr)
{
    *ptr *= 2;
}

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(3);
    std::unique_ptr<int[]> tab = std::make_unique<int[]>(10);

    *ptr = 3;
    for (int i = 0; i < 10; ++i) tab[i] = i;

    // std::unique_ptr<int> p2 = ptr;
    std::unique_ptr<int> p2 = std::move(ptr);

    ptr = process(std::move(p2));
    process(ptr.get());

    ptr = nullptr;

    return 0;
}
