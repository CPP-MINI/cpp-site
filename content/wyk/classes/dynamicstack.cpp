#include <iostream>
#include <vector>

class DynamicStack
{
    const int capacity;
    int* tab;
    int size;

public:
    DynamicStack(int capacity = 10) : capacity(capacity), size(0)
    {
        tab = new int[capacity];
    }

    ~DynamicStack() { delete[] tab; }

    void push(int val)
    {
        if (size == capacity) return;
        tab[size++] = val;
    }

    [[nodiscard]] int top() const
    {
        return size > 0 ? tab[size - 1] : -1;
    }

    int pop()
    {
        if (size == 0) return -1;
        return tab[--size];
    }

    bool empty() const
    {
        return size == 0;
    }

    int full() const
    {
        return size == capacity;
    }
};

int main()
{
    DynamicStack s(5);

    int i = 0;
    while (!s.full())
    {
        std::cout << "push: " << i << std::endl;
        s.push(i++);
    }

    while (!s.empty())
    {
        std::cout << "pop: " << s.pop() << std::endl;
    }

    return 0;
}
