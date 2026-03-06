#include <iostream>
#include <string>

class Int
{
    int value;

   public:
    Int(int value) : value(value) {}

    int get() const { return value; }

    Int operator+(Int other) { return Int(value + other.value); }

    Int operator+() { return *this; }

    Int operator-() { return Int(-value); }

    Int& operator++()
    {
        ++value;
        return *this;
    }

    Int& operator--()
    {
        --value;
        return *this;
    }

    Int operator++(int)
    {
        Int tmp = *this;
        ++value;
        return tmp;
    }

    Int operator--(int)
    {
        Int tmp = *this;
        --value;
        return tmp;
    }
};

std::ostream& operator<<(std::ostream& os, const Int& i)
{
    os << "Int(" << i.get() << ")";
    return os;
}

int main()
{
    Int x = 3;
    std::cout << "x = " << x << std::endl;
    Int unary_plus = +x;
    std::cout << "unary_plus = " << unary_plus << std::endl;
    std::cout << "x = " << x << std::endl;
    Int unary_minus = -x;
    std::cout << "unary_minus = " << unary_minus << std::endl;
    std::cout << "x = " << x << std::endl;

    Int pre_inc = ++x;
    std::cout << "pre_inc = " << pre_inc << std::endl;
    std::cout << "x = " << x << std::endl;
    Int pre_dec = --x;
    std::cout << "pre_dec = " << pre_dec << std::endl;
    std::cout << "x = " << x << std::endl;
    Int post_inc = x++;
    std::cout << "post_inc = " << post_inc << std::endl;
    std::cout << "x = " << x << std::endl;
    Int post_dec = x--;
    std::cout << "post_dec = " << post_dec << std::endl;
    std::cout << "x = " << x << std::endl;

    return 0;
}
