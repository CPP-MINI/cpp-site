#include <iostream>
#include <array>

constexpr bool is_prime(std::size_t n) noexcept {
    if (n <= 1) return false;
    for (std::size_t i = 2; i * i <= n; i++)   if (n % i == 0) return false;
    return true;
}

constexpr unsigned int nth_prime(std::size_t i) noexcept {
    std::size_t k = 1;
    for  (std::size_t counter = 0; counter < i; ++k)
    {
        if (is_prime(k)) ++counter;
        if (counter == i) return k;
    }
    return 0;
}

constexpr int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char** argv)
{
    std::cout << "is_prime(10000) = " << is_prime(10000) << std::endl;
    std::cout << "is_prime(48611) = " << is_prime(48611) << std::endl;
    static_assert(is_prime(10000) == false);
    static_assert(is_prime(48611) == true);
    std::cout << "nth_prime(10000) = " << nth_prime(10000) << std::endl;
    static_assert(nth_prime(5000) == 48611);
    std::cout << "fib(10) = " << fib(10) << std::endl;
    static_assert(fib(10) == 55);

    std::array<int, fib(10)> arr = {};
    std::cout << "created std::array<int, " << arr.size() << ">" << std::endl;

    return 0;
}
