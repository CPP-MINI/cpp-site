#include <iostream>

template <int N>
struct value {};

template<int N>
std::ostream& operator<<(std::ostream& os, const value<N>& v)
{
    os << N;
    return os;
}

template<typename V1, typename V2>
struct add;

template<int N1, int N2>
struct add<value<N1>, value<N2>>
{
    using result_type = value<N1 + N2>;
};

template<typename V1, typename V2>
struct mul;

template<int N1, int N2>
struct mul<value<N1>, value<N2>>
{
    using result_type = value<N1 * N2>;
};

int main()
{
    using a = value<2>;
    using b = value<3>;
    using c = value<4>;
    using x = mul<a, b>::result_type; // x = 2 * 3
    using y = add<x, c>::result_type; // y = 2 * 3 + 4

    std::cout << "x = " << x{} << std::endl;
    std::cout << "y = " << y{} << std::endl;

    return 0;
}
