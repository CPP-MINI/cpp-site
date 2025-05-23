#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

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

#endif
