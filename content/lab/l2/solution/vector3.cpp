#include "vector3.hpp"
#include <cmath>
#include <cstring>
#include <iostream>

namespace l2
{

void vector3_init(Vector3& vec)
{
    memset(vec.v.buffer, 0, sizeof(Vector3::internal_representation));
}

void vector3_init(Vector3& vec, double x, double y, double z)
{
    vec.v.x = x;
    vec.v.y = y;
    vec.v.z = z;
}

double vector3_length(const Vector3& vec)
{
    double res = 0.0;
    for (int i = 0; i < Vector3::VECTOR_SIZE; ++i)
        res += vec.v.buffer[i] * vec.v.buffer[i];
    return sqrt(res);
}

void vector3_mul(Vector3& vec, double a)
{
    for (int i = 0; i < Vector3::VECTOR_SIZE; ++i)
        vec.v.buffer[i] *= a;
}

Vector3 vector3_add(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.v.x = lhs.v.x + rhs.v.x;
    result.v.y = lhs.v.y + rhs.v.y;
    result.v.z = lhs.v.z + rhs.v.z;
    return result;
}

void vector3_print(const Vector3& v)
{
    std::cout << "[" << v.v.x << "," << v.v.y << "," << v.v.z << "] " << vector3_length(v) << std::endl;
}

}  // namespace l2
