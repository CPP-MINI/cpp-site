#include "point.hpp"

template <typename PointType>
class rectangle
{
    PointType _lb;
    PointType _tr;

   public:
    rectangle();

    rectangle(PointType lb, PointType tr);

    double left() { return _lb.x(); }
    double right() { return _tr.x(); }
    double bottom() { return _lb.y(); }
    double top() { return _tr.y(); }

    double area();
};

template <typename PointType>
rectangle<PointType>::rectangle() : _lb{}, _tr{}
{
}

template <typename PointType>
rectangle<PointType>::rectangle(PointType lb, PointType tr) : _lb(lb), _tr(tr)
{
    if (lb.x() > tr.x())
        std::swap(lb.x(), tr.x());
    if (lb.y() > tr.y())
        std::swap(lb.y(), tr.y());
}

template <typename PointType>
double rectangle<PointType>::area()
{
    return (_tr.x() - _lb.x()) * (_tr.y() - _lb.y());
}

int main()
{
    rectangle<point<double>> rd { point<double>(1.0, 1.0), point<double>(2.5, 2.5) };
    std::cout << "area = " << rd.area() << std::endl;
    return 0;
}
