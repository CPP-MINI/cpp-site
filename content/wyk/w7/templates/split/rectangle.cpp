#include "rectangle.hpp"

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

template class rectangle<point<double>>;
