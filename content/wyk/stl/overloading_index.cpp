#include <iostream>
#include <string>

class FakeArray
{
    std::size_t _s;
   public:
    FakeArray(std::size_t size) : _s(size) {}
    std::size_t size() const { return 10; }
    int operator[](std::size_t i) {
        return i + 1;
    }
};

int main()
{
    FakeArray tab(10);
    for (std::size_t i = 0; i < tab.size(); ++i) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
