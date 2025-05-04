#include <iostream>

class Base
{
   public:
    int value = 0;
};

class A : public Base
{
   public:
    int x;
    A(int x) : x{x} {}
};

class B : public Base
{
   public:
    int x;
    B(int x) : x{x} {}
};

class C : public A, public B
{
   public:
    int x;

    C() : A{1}, B{2}, x{3} {}

    void print() const
    {
        std::cout << A::x << ", " << B::x << ", " << x << std::endl;
        // std::cout << value << std::endl;
        std::cout << A::value << std::endl;
        std::cout << B::value << std::endl;
    }
};

int main()
{
    C c;
    c.print();
    return 0;
}
