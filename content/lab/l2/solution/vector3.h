#pragma once

namespace l2 {

class Vector3{
private:
    static constexpr int VECTOR_SIZE = 3;



    using vector = union{
        struct
        {
            double x,y,z;
        };
        double buffer[VECTOR_SIZE];
    };

    static_assert(sizeof(vector) == sizeof(double) * 3, "Your vector structure has to be properly sized!");

public:
    vector v;

    Vector3();
    Vector3(double x, double y, double z);

    double length() const ;
};

} // namespace l2
