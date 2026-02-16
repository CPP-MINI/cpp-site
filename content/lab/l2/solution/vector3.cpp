#include "vector3.hpp"
#include <cmath>
#include <cstring>
#include <iostream>

namespace l2
{

void vector3_init(Vector3& vec)
{
    memset(vec.v, 0, sizeof(Vector3::internal_representation));
}

void vector3_init(Vector3& vec, double x, double y, double z)
{
    vec.v[0] = x;
    vec.v[1] = y;
    vec.v[2] = z;
}

double vector3_length(const Vector3& vec)
{
    double res = 0.0;
    for (int i = 0; i < Vector3::VECTOR_SIZE; ++i)
        res += vec.v[i] * vec.v[i];
    return sqrt(res);
}

void vector3_mul(Vector3& vec, double a)
{
    for (int i = 0; i < Vector3::VECTOR_SIZE; ++i)
        vec.v[i] *= a;
}

Vector3 vector3_add(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.v[0] = lhs.v[0] + rhs.v[0];
    result.v[1] = lhs.v[1] + rhs.v[1];
    result.v[2] = lhs.v[2] + rhs.v[2];
    return result;
}

void vector3_print(const Vector3& v)
{
    std::cout << "[" << vector3_x(v) << "," << vector3_y(v) << "," << vector3_z(v) << "] " << vector3_length(v) << std::endl;
}

double vector3_x(const Vector3& vec)
{
    return vec.v[0];
}

double vector3_y(const Vector3& vec)
{
    return vec.v[1];
}

double vector3_z(const Vector3& vec)
{
    return vec.v[2];
}

}  // namespace l2
