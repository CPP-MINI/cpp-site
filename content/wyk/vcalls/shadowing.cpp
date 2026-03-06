#include <iostream>

class Base
{
public:
    int value = 10;
    void bump() { value++; }
};

class Derived : public Base
{
public:
    int value = 20;
    void bump() { value--; }
    void bump_base() { Base::bump(); }
};

int main()
{
    Derived d;
    d.bump();
    std::cout << d.value << " at " << static_cast<void*>(&d.value) << std::endl;
    d.Base::bump();
    std::cout << d.Base::value << " at " << static_cast<void*>(&d.Base::value) << std::endl;

    return 0;
}
