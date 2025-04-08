 #include <string>
#include <iostream>

class vector3d {
    float _x, _y, _z;
public:
    vector3d(float x, float y, float z) : _x(x), _y(y), _z(z) {
        std::cout << "constructed vector3d(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
    }

    vector3d(const vector3d& other) : _x(other._x), _y(other._y), _z(other._z) {
        std::cout << "copied vector3d(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
    }

    float x() const { return _x; }
    float y() const { return _y; }
    float z() const { return _z; }

    vector3d& operator+=(const vector3d& other) {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    vector3d operator+(const vector3d& other) const {
        vector3d result = *this;
        result += other;
        return result;
    }

    vector3d& operator*=(float value) {
        _x *= value;
        _y *= value;
        _z *= value;
        return *this;
    }

    vector3d operator*(float value) const {
        vector3d result = *this;
        result *= value;
        return result;
    }
};

vector3d operator*(float value, const vector3d& other) {
    vector3d result = other;
    result *= value;
    return result;
}

std::ostream& operator<<(std::ostream& os, const vector3d& v) {
    os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return os;
}

int main() {
    std::string str = "Hello";
    str += " World";

    vector3d v1(1, 2, 3);
    v1 += 2 * vector3d(1, 0, 2);
    v1 *= 2;
    std::cout << v1 << std::endl;

    return 0;
}
