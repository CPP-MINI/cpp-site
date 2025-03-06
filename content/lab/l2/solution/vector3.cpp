#include "vector3.h"
#include <cmath>
#include <cstring>

namespace l2
{

Vector3::Vector3() { memset(v.buffer, 0, sizeof(Vector3::vector)); }

Vector3::Vector3(double x, double y, double z)
{
    v.x = x;
    v.y = y;
    v.z = z;
}

double Vector3::length() const
{
    double res = 0.0;
    for (int i = 0; i < VECTOR_SIZE; ++i)
        res += v.buffer[i] * v.buffer[i];
    return sqrt(res);
}

}  // namespace l2
