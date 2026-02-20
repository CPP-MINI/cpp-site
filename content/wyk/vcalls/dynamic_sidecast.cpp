#include <iostream>

struct Base
{
    virtual ~Base() = default;
};

struct A : Base
{
    int a = 0;
};

struct B : Base
{
    int b = 0;
};

struct Derived : A, B
{
};

int main()
{
    Derived obj;

    A& a = obj; // upcast
    a.a = 1;
    B& b = dynamic_cast<B&>(a); // sidecast!
    b.b = 2;
    Derived& d = dynamic_cast<Derived&>(b); // downcast

    std::cout << d.a << " " << d.b << std::endl;

    return 0;
}
