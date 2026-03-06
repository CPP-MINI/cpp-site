#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

template <typename T>
class point
{
    T _x;
    T _y;

   public:
    point() : _x{}, _y{} {}
    point(T x, T y) : _x(x), _y(y) {}

    T& x() { return _x; }
    T& y() { return _y; }

    T x() const { return _x; }
    T y() const { return _y; }
};

template <typename T>
T distance2(const point<T>& a, const point<T>& b)
{
    auto dx = a.x() - b.x();
    auto dy = a.y() - b.y();
    return dx * dx + dy * dy;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const point<T>& p)
{
    os << "(" << p.x() << ", " << p.y() << ")";
    return os;
}

#endif
