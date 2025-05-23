#include <cmath>

class point
{
    float _x, _y;
public:
    constexpr point() : _x{0}, _y{0} {}
    constexpr point(float x, float y) : _x{x}, _y{y} {}
    [[nodiscard]] constexpr float x() const { return _x; }
    [[nodiscard]] constexpr float y() const { return _y; }
};

constexpr float distance(point a, point b)
{
    float dx = a.x() - b.x();
    float dy = a.y() - b.y();
    return std::sqrt(dx * dx + dy * dy);
}

int main(int argc, char** argv)
{
    constexpr float epsilon = 1e-6;
    constexpr point a = {1.0, 2.0};
    constexpr point b = {4.0, 6.0};

    static_assert(distance(a, b) - 5.0 < epsilon, "too distant!");

    return 0;
}
