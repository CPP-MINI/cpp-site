class A {};

A get_A() { return A(); }

int main() {
    auto x = 1; // x is int
    auto a = A(); // a is A
    auto a2 = get_A(); // a2 is A

    auto& rx = x; // rx is int&
    auto& ra = a; // ra is A&

    const auto& rxa = a; // rxa is const A&
    const auto& rxa2 = get_A(); // rxa2 is const A&
    return 0;
}
