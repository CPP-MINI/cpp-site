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
    virtual float run(float time) {
        std::cout << "Vehicle::run(" << time << "s)" << std::endl;
        const float speed = 1.0f;
        _position += time * speed;
        return _position;
    }
};

class Car : public Vehicle
{
   protected:
    float speed = 0.0f;
    float acceleration;
    Car(std::string name, float acceleration) : Vehicle(std::move(name)), acceleration(acceleration) {}

   public:
    float run(float time) override {
        std::cout << "Car::run(" << time << "s)" << std::endl;
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
    float run(float time) override {
        std::cout << "Bike::run(" << time << "s)" << std::endl;
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

    for (float time = 0.0f; time < 3.0f; time += 1.0f) {
        Vehicle* vehicles[] = {&b, &dc, &ec};
        std::cout << "======= " << time << "s =======" << std::endl;
        for (auto v : vehicles) {
            v->run(1.0f);
        }
        for (auto v : vehicles) {
            print(*v);
        }
    }

    return 0;
}
