#include <iostream>

struct BaseA
{
    int first;
};

struct BaseB
{
    int second;
};

struct Derived : BaseA, BaseB
{
    int derived;
};

void processA(BaseA* obj) { std::cout << "process(BaseA* obj = " << static_cast<void*>(obj) << ")\n"; }

void processB(BaseB* obj) { std::cout << "process(BaseB* obj = " << static_cast<void*>(obj) << ")\n"; }

int main()
{
    Derived d = {1, 2, 3};
    std::cout << "&d = " << static_cast<void*>(&d) << "\n";
    BaseA* a = &d;
    BaseB* b = &d;
    std::cout << "a = " << static_cast<void*>(a) << "\n";
    std::cout << "b = " << static_cast<void*>(b) << "\n";
    std::cout << "b - a = " << reinterpret_cast<std::byte*>(b) - reinterpret_cast<std::byte*>(a) << "b\n";

    processA(&d);
    processB(&d);

    return 0;
}
