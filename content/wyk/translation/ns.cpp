#include <iostream>
#include <string>

std::string ns = "global";

namespace foo
{
std::string ns = "foo";

namespace goo
{
std::string ns = "goo";
}

void fun()
{
    std::cout << "from foo namespace:\n"
        << "ns = " << ns << '\n'
        << "goo::ns = " << goo::ns << '\n'
        << "::ns = " << ::ns << std::endl;
}
}

void fun()
{
    std::cout << "from global namespace:\n"
        << "ns = " << ns << '\n'
        << "foo::ns = " << foo::ns << '\n'
        << "foo::goo::ns = " << foo::goo::ns << std::endl;
}

int main()
{
    fun();
    foo::fun();
    return 0;
}
