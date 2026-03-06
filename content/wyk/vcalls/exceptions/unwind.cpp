#include <vector>
#include <stdexcept>
#include <iostream>

class DynamicInt {
    int* ptr;
   public:
    DynamicInt(int value) : ptr(new int{value}) {
        std::cout << "Creating DynamicInt = " << value << "\n";
    }
    ~DynamicInt() {
        std::cout << "Destroying DynamicInt = " << *ptr << "\n";
        delete ptr;
    }
};

void do_work(int value) {
    if (value <= 0) {
        std::cout << "Zero reached\n";
        throw std::runtime_error("Zero reached");
    }
    DynamicInt val(value);
    do_work(value - 1);
}

int main() {
    try {
     do_work(5);
    } catch (std::exception& e) {
        std::cout << "do_work() failed with exception = " << e.what() << "\n";
    }
    return 0;
}
