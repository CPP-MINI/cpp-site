#include <iostream>
#include <string>

class LessThanFunc
{
    int value;
   public:
    LessThanFunc(int value) : value(value) {}

    int val() const { return value; }

    bool operator()(int x) {
        return x < value;
    }
};

std::ostream& operator<<(std::ostream& os, const LessThanFunc& f) {
    os << "<" << f.val();
    return os;
}

int main()
{
    LessThanFunc f(3);
    std::cout << "4" << f << " = " << std::boolalpha << f(4) << std::endl;
    std::cout << "2" << f << " = " << std::boolalpha << f(2) << std::endl;
    return 0;
}
