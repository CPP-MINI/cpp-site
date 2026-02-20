#include <iostream>
#include <vector>

template <typename T, typename U>
class pair
{
    T t;
    U u;

   public:
    pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}
    T& first() { return t; }
    U& second() { return u; }
    const T& first() const { return t; }
    const U& second() const { return u; }
};

template <typename T, typename U>
pair<T, U> make_pair(const T& t, const U& u)
{
    return pair<T, U>(t, u);
}

int main()
{
    pair p1(std::vector<int>{1, 2}, 4.0);  // pair<vector<int>, double>>
    auto p2 = make_pair(3.0f, 50);         // pair<float, int>
    return 0;
}
