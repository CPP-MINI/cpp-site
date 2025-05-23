#include <iostream>

template <typename T>
class point
{
    T _x;
    T _y;
public:
    point() : _x{}, _y{} {}
    point(T x, T y) : _x(x), _y(y) {}

    T x() const { return _x; }
    T y() const { return _y; }
};

template<typename T>
void print(const point<T>& p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

int main()
{
    point<int> pi{1, 2};
    point<float> pf(1.5f, 2.1f);

    print<int>(pi);
    print<float>(pf);

    return 0;
}