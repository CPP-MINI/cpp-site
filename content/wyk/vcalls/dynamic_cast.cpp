#include <iostream>
#include <typeinfo>
#include <cmath>

struct Shape
{
    virtual ~Shape() = default;
    virtual float area() = 0;
};

struct Square : Shape
{
    float size;
    explicit Square(float size) : size{size} {}
    float area() override { return size * size; }
};

struct Circle : Shape
{
    float radius;
    explicit Circle(float radius) : radius{radius} {}
    float area() override { return M_PI * radius * radius; }
};

int main()
{
    Shape* shapes[] = {new Square(2), new Circle(1)};

    for (auto shape : shapes)
    {
        dynamic_cast<Circle&>(*shape);

        auto square = dynamic_cast<Square*>(shape);
        if (square != nullptr) {
            std::cout << "It's a square!\n";
            square->size = 10;
        }

        auto circle = dynamic_cast<Circle*>(shape);
        if (circle != nullptr) {
            std::cout << "It's a circle!\n";
            circle->radius = 10;
        }

        std::cout << "Area is " << shape->area() << std::endl;
        delete shape;
    }

    return 0;
}
