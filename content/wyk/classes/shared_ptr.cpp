#include <memory>

class Point
{
    float x, y;
public:
    Point(float a, float b) : x{a}, y{b} {}
};

int main()
{
    std::shared_ptr<Point> ptr = std::make_shared<Point>(1.0, 2.0);
    std::shared_ptr<Point> ptr2 = ptr;
    ptr = nullptr;
    return 0;
}
