#pragma once

namespace l2
{

class Vector3
{
   private:
    static const int VECTOR_SIZE = 3;

    using internal_representation = union
    {
        struct
        {
            double x, y, z;
        };
        double buffer[VECTOR_SIZE];
    };

    static_assert(sizeof(internal_representation) == sizeof(double) * 3,
                  "Your vector structure has to be properly sized!");
    static_assert(alignof(internal_representation) == alignof(double),
                  "Your vector structure has to be aligned as double!");

   public:
    internal_representation v;

    Vector3();
    Vector3(double x, double y, double z);

    double length() const;
    void mul(double a);
};

Vector3 vector3_add(const Vector3& lhs, const Vector3& rhs);
void vector3_print(const Vector3& v);

static const Vector3 BaseVector1{1, 0, 0};
static const Vector3 BaseVector2{0, 1, 0};
static const Vector3 BaseVector3{0, 0, 1};

}  // namespace l2
