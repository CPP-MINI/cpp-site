#include <iostream>

class A {
    std::string tag;
public:
    A(std::string tag) : tag{tag} { std::cout << "A(" << tag << ")\n"; }
    ~A() { std::cout << "~A(" << tag << ")\n"; }
};

class B {
    std::string tag;
public:
    B(std::string tag) : tag{tag} { std::cout << "B(" << tag << ")\n"; }
    ~B() { std::cout << "~B(" << tag << ")\n"; }
};

class C {
    A a;
    B b;
    std::string tag;
public:
    C(std::string tag) : a{tag}, b{tag}, tag{tag} { std::cout << "C(" << tag << ")\n"; }
    ~C() { std::cout << "~C(" << tag << ")\n"; }
};

C a("static");

int main() {
    C a("automatic");

    auto pa = new C("dynamic");
    delete pa;

    return 0;
}
