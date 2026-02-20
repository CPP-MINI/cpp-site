#include <iostream>
#include <utility>

class M
{
public:
    M() { std::cout << "default constructor\n"; }
    ~M() { std::cout << "destructor\n"; }
    M(const M& other) { std::cout << "copy constructor\n"; }
    M(M&& other) { std::cout << "move constructor\n"; }
    M& operator=(const M& other) { std::cout << "copy assignment\n"; return *this; }
    M& operator=(M&& other) { std::cout << "move assignment\n"; return *this; }
};

class A
{
public:
    M m;

    A() = default;

    // TODO: Try uncommenting one-by-one

    // ~A() {}

    // A(const A& other) : m{other.m} {}

    // A(const A& other) = delete;

    // A(A&& other) : m{std::move(other.m)} {}

    // A(A&& other) = delete;

    // A& operator=(const A& other) { m = other.m; return *this; }

    // A& operator=(const A& other) = delete;

    // A& operator=(A&& other) { m = std::move(other.m); return *this; }

    // A& operator=(A&& other) = delete;

};

int main()
{
    A a, b;

    A copy = a;
    A moved = std::move(a);

    copy = b;
    moved = std::move(b);

    return 0;
}
