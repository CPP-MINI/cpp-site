#pragma once

namespace l2
{

class Vector3
{
   private:
    static constexpr int VECTOR_SIZE = 3;

    using internal_representation = int;  // STAGE 1: Define me!

    static_assert(sizeof(internal_representation) == sizeof(double) * 3,
                  "Your internal_representation structure has to be properly sized!");
    static_assert(alignof(internal_representation) == alignof(double),
                  "Your vector structure has to be aligned as double!");

   public:
    internal_representation v;

    Vector3();
    Vector3(double x, double y, double z);

    double length() const;
    void mul(double a);
};

}  // namespace l2
