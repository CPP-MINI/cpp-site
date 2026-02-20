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
        const std::type_info& type = typeid(*shape);
        std::cout << "Shape of type " << type.name() << std::endl;
        if (type == typeid(Square)) {
            std::cout << "It's a square!\n";
        } else if (type == typeid(Circle)) {
            std::cout << "It's a circle!\n";
        }
        std::cout << "Area is " << shape->area() << std::endl;
        delete shape;
    }

    return 0;
}
