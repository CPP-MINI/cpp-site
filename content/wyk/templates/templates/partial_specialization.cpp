#include <cstring>
#include <iostream>
#include <vector>

template <typename T>
struct A
{
    void print()
    {
        std::cout << "A<T>" << std::endl;
    }
};

template <typename T>
struct A<T*>
{
    void print()
    {
        std::cout << "A<T*>" << std::endl;
    }
};


template<typename T>
struct A<std::vector<T>>
{
    void print()
    {
        std::cout << "A<std::vector<T>>" << std::endl;
    }
};

int main()
{
    A<int>{}.print();
    A<int*>{}.print();
    A<std::vector<int>>{}.print();
    return 0;
}
