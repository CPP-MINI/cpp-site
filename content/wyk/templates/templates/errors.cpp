#include <iostream>
#include <vector>

template <typename PointType>
class rectangle
{
    PointType _lb;
    PointType _tr;

public:
    rectangle() : _lb{}, _tr{} {}

    rectangle(PointType lb, PointType tr) : _lb(lb), _tr(tr)
    {
        if (lb.x() > tr.x()) std::swap(lb.x(), tr.x());
        if (lb.y() > tr.y()) std::swap(lb.y(), tr.y());
    }

    double left() { return _lb.x(); }
    double right() { return _tr.x(); }
    double bottom() { return _lb.y(); }
    double top() { return _tr.y(); }

    double area()
    {
        return (_tr.x() - _lb.x()) * (_tr.y() - _lb.y());
    }
};

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
    T y() const { return  _y; }
};

using pointi = point<int>;
using pointd = point<double>;

struct string_point
{
    std::string _x;
    std::string _y;

    string_point(std::string x, std::string y) : _x{std::move(x)}, _y{std::move(y)} {}

    std::string& x() { return _x; }
    std::string& y() { return _y; }

    std::string x() const { return _x; }
    std::string y() const { return  _y; }
};

// template class rectangle<string_point>;

int main()
{
    rectangle<pointd> rd { pointd(1.0, 1.0), point(2.5, 2.5) };
    std::cout << "area = " << rd.area() << std::endl;
    rectangle<pointi> ri{pointi(1, 1), pointi(2, 2)};
    std::cout << "area = " << ri.area() << std::endl;

    rectangle<int> rint;  // ok?
    // rectangle<int> rint2 {1, 2};
    // rint2.area();

    rectangle<string_point> rstr {{"hey", "hi"}, {"hello", "cpp"}};
    // rstr.area();

    return 0;
}