#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

#include "point.hpp"

using pointd = point<double>;

pointd make_point(double x, double y);

pointd make_random_point();

pointd get_furthest(pointd center, std::vector<pointd> points);

#ifdef EXTERN_POINTD
extern template class point<double>;
#endif

#endif
