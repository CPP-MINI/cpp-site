#include "utils.hpp"

#include <algorithm>
#include <random>

pointd make_point(double x, double y)
{
    return pointd(x, y);
}

pointd make_random_point()
{
    std::random_device rd;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    auto x = distribution(rd);
    auto y = distribution(rd);
    return make_point(x, y);
}

pointd get_furthest(pointd center, std::vector<pointd> points)
{
    std::vector<double> distances(points.size());

    struct distance_comparator
    {
        pointd c;
        double operator()(const pointd& a, const pointd& b) {
            return distance2(c, a) < distance2(c, b);
        }
    };

    auto max_it = std::max_element(points.begin(), points.end(), distance_comparator{center});
    return *max_it;
}

#ifdef EXTERN_POINTD
template class point<double>;
#endif
