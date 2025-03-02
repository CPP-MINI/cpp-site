#pragma once

namespace l2 {

class Vector3{
private:
    static constexpr int VECTOR_LENGTH = 3;

    union vector{
        struct {
            double x,y,z;
        };
        double buffer[VECTOR_LENGTH];
    };

public:
    vector v;

    Vector3();
    Vector3(double x, double y, double z);

    double length() const ;
};

}
