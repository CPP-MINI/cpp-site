#include <iostream>
#include <vector>

class Stack
{
    int tab[10];
    int size;

public:
    Stack() : size(0)
    {
        std::cout << "constructing stack" << std::endl;
    }

    void push(int val)
    {
        if (size == 10) return;
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
};

int main()
{
    std::cout << "hey!" << std::endl;
    Stack s;
    std::cout << "i have a stack!" << std::endl;

    s.push(1);
    s.push(2);
    s.push(3);

    while (!s.empty())
    {
        std::cout << "pop: " << s.pop() << std::endl;
    }

    return 0;
}


