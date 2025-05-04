#include <iostream>

class Vehicle
{
   protected:
    float _position = 0.0;
    std::string _name;
    Vehicle(std::string name) : _name(name) {}
   public:
    const std::string& name() const { return _name; }
    float position() const { return _position; }
};

class Car : public Vehicle
{
   protected:
    float speed;
    float acceleration;
    Car(std::string name, float acceleration) : Vehicle(std::move(name)), acceleration(acceleration) {}

   public:
    float run(float time) {
        _position += speed * time;
        speed += acceleration * time;
        return _position;
    }
};

class DieselCar : public Car
{
   public:
    DieselCar(std::string name) : Car(name, 1.0f) {}
};

class ElectricCar : public Car
{
   public:
    ElectricCar(std::string name) : Car(name, 3.0f) {}
};

class Bike : public Vehicle
{
   public:
    Bike(std::string name) : Vehicle(std::move(name)) {}
    float run(float time) {
        const float speed = 0.2f;
        _position += speed * time;
        return _position;
    }
};

void print(const Vehicle& v) {
    std::cout << "Vehicle " << v.name() << " at " << v.position() << "m" << std::endl;
}

int main() {
    Bike b ("Romet");
    DieselCar dc("Toyota Fortuner");
    ElectricCar ec ("Ford Mustang Mach-E");

    std::cout << "Bike " << b.name() << " at " << static_cast<void*>(&b) << std::endl;
    std::cout << "DieselCar " << dc.name() << " at " << static_cast<void*>(&dc) << std::endl;
    std::cout << "ElectricCar " << ec.name() << " at " << static_cast<void*>(&ec) << std::endl;

    {
        // Refer to objects through pointers to a base type
        Vehicle* vb = &b;
        Vehicle* vdc = &dc;
        Vehicle* vec = &ec;
        std::cout << "Bike " << vb->name() << " at " << static_cast<void*>(vb) << std::endl;
        std::cout << "DieselCar " << vdc->name() << " at " << static_cast<void*>(vdc) << std::endl;
        std::cout << "ElectricCar " << vec->name() << " at " << static_cast<void*>(vec) << std::endl;
    }

    {
        // Refer to objects through references to a base type
        print(b);
        print(dc);
        print(ec);
    }

    {
        // Store pointers to objects of different types in an array
        Vehicle* vehicles[] = {&b, &dc, &ec};
        for (auto v : vehicles) {
            print(*v);
        }
    }

    return 0;
}
