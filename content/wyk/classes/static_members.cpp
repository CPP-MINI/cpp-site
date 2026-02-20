#include <memory>
#include <iostream>

class Entry {
 static int count;
public:
 static int getCount() { return count; }

 Entry() { ++count; }

 ~Entry() { --count; }
};

int Entry::count = 0;

int main() {
    std::cout << "[0] count = " << Entry::getCount() << std::endl;

    Entry e1, e2;

    std::unique_ptr<Entry> e3 = std::make_unique<Entry>();

    std::cout << "[1] count = " << Entry::getCount() << std::endl;

    {
        Entry e4;

        std::cout << "[2] count = " << Entry::getCount() << std::endl;

        e3 = nullptr;
    }

    std::cout << "[3] count = " << Entry::getCount() << std::endl;

    Entry e4;

    std::cout << "[4] count = " << Entry::getCount() << std::endl;

    return 0;
}
