#include <iostream>

class Rectangle
{
    struct Point
    {
        float x, y;
    };

    Point a, b;

public:
    Rectangle(float x0, float y0, float x1, float y1) : a{x0, y0}, b{x1, y1}
    {
    }

    float area() const
    {
        return (b.x - a.x) * (b.y - a.y);
    }
};

int main(int argc, char** argv)
{
    Rectangle rec(0.0f, 0.0f, 2.0f, 1.0f);
    // Rectangle::Point pub = {1.0f, 1.0f};
    std::cout << "area = " << rec.area() << std::endl;
    return 0;
}
