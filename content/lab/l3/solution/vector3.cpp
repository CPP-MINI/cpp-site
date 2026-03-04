#include "vector3.hpp"
#include <cmath>
#include <cstring>
#include <iostream>

namespace l2
{

Vector3::Vector3() { memset(v.buffer, 0, sizeof(Vector3::internal_representation)); }

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

void Vector3::mul(double a)
{
    for (int i = 0; i < VECTOR_SIZE; ++i)
        v.buffer[i] *= a;
}

Vector3 vector3_add(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3{
        lhs.v.x + rhs.v.x,
        lhs.v.y + rhs.v.y,
        lhs.v.z + rhs.v.z,
    };
}

void vector3_print(const Vector3& v)
{
    std::cout << "[" << v.v.x << "," << v.v.y << "," << v.v.z << "] " << v.length() << std::endl;
}

}  // namespace l2
