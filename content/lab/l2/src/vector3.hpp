#pragma once

namespace l2
{

struct Vector3
{
    static const int VECTOR_SIZE = 3;

    double v[VECTOR_SIZE];  // STAGE 1: Define me!
};

void vector3_init(Vector3& vec);
void vector3_init(Vector3& vec, double x, double y, double z);
double vector3_length(const Vector3& vec);
void vector3_mul(Vector3& vec, double a);

double vector3_x(const Vector3& vec);
double vector3_y(const Vector3& vec);
double vector3_z(const Vector3& vec);

}  // namespace l2
