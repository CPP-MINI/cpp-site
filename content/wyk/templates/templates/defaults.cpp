#include <iostream>

template<typename T = int, typename U = int>
class pair {
    T t;
    U u;
public:
    pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}
    T& first() { return t; }
    U& second() { return u; }
    const T& first() const { return t; }
    const U& second() const { return u; }
};


int main()
{
    pair<> p1(1, 2);
    pair<float> p2(1.1, 2);
    pair<float, double> p3(1.1, 2.2);

    return 0;
}
