#include "rectangle.hpp"

int main()
{
    rectangle<point<double>> rd { point<double>(1.0, 1.0), point<double>(2.5, 2.5) };
    std::cout << "area = " << rd.area() << std::endl;
    return 0;
}
