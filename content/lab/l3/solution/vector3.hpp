#pragma once

namespace l2
{

struct Vector3
{
    static const int VECTOR_SIZE = 3;

    double v[VECTOR_SIZE];
};

void vector3_init(Vector3& vec);
void vector3_init(Vector3& vec, double x, double y, double z);
double vector3_length(const Vector3& vec);
void vector3_mul(Vector3& vec, double a);
Vector3 vector3_add(const Vector3& lhs, const Vector3& rhs);
void vector3_print(const Vector3& v);

double vector3_x(const Vector3& vec);
double vector3_y(const Vector3& vec);
double vector3_z(const Vector3& vec);

static const Vector3 BaseVector1{{1, 0, 0}};
static const Vector3 BaseVector2{{0, 1, 0}};
static const Vector3 BaseVector3{{0, 0, 1}};

}  // namespace l2
