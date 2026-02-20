#include "headers/point.hpp"

template class point<int>;
template class point<float>;

point<double> make_pointd()
{
    point<double> d;
    return d;
}
