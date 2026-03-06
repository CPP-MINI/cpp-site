#include <iostream>

class Base
{
   public:
    Base& operator=(const Base&)
    {
        std::cout << "operator=(const Base&)\n";
        return *this;
    };
    Base& operator=(Base&&)
    {
        std::cout << "operator=(Base&&)\n";
        return *this;
    };
};

class Derived : public Base
{
   public:
//    Derived& operator=(const Derived& other)
//    {
//        std::cout << "operator=(const Derived&)\n";
//        Base::operator=(other);
//        return *this;
//    };
//    Derived& operator=(Derived&& other)
//    {
//        std::cout << "operator=(Derived&&)\n";
//        Base::operator=(std::move(other));
//        return *this;
//    };
};

int main()
{
    Derived o1, o2;
    o1 = o2;
    o1 = std::move(o2);
    return 0;
}
