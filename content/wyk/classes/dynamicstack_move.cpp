#include <iostream>
#include <vector>

class DynamicStack
{
    int capacity;
    int* tab;
    int size;

public:
    DynamicStack(int capacity = 10) : capacity(capacity), size(0)
    {
        std::cout << "constructing stack (" << size << "/" << capacity << ")" << std::endl;
        tab = new int[capacity];
    }

    DynamicStack(const DynamicStack& other)
        : capacity(other.capacity),
          size(other.size)
    {
        std::cout << "copy constructing stack (" << size << "/" << capacity << ")" << std::endl;
        tab = new int[capacity];
        for (int i = 0; i < size; ++i) {
            tab[i] = other.tab[i];
        }
    }

    DynamicStack(DynamicStack&& other)
        : capacity(other.capacity),
          size(other.size),
          tab(other.tab)
    {
        std::cout << "move constructing stack (" << size << "/" << capacity << ")" << std::endl;
        other.capacity = 0;
        other.size = 0;
        other.tab = nullptr;
    }

    ~DynamicStack()
    {
        std::cout << "destroying stack (" << size << "/" << capacity << ")" << std::endl;
        if (tab) delete[] tab;
    }

    DynamicStack& operator=(const DynamicStack& other)
    {
        std::cout << "assigning stack (" << size << "/" << capacity << ") <- (" << other.size << "/" << other.capacity << ")" << std::endl;
        if (this == &other) return *this;
        if (capacity != other.capacity)
        {
            delete[] tab;
            tab = new int[other.capacity];
            capacity = other.capacity;
        }
        size = other.size;
        for (int i = 0; i < size; ++i) {
            tab[i] = other.tab[i];
        }
        return *this;
    }

    DynamicStack& operator=(DynamicStack&& other)
    {
        std::cout << "move assigning stack (" << size << "/" << capacity << ") <- (" << other.size << "/" << other.capacity << ")" << std::endl;
        if (this == &other) return *this;
        delete[] tab;
        capacity = other.capacity;
        size = other.size;
        tab = other.tab;
        other.capacity = 0;
        other.size = 0;
        other.tab = nullptr;
        return *this;
    }

    void push(int val)
    {
        if (size == capacity) return;
        tab[size++] = val;
        std::cout << "pushed to stack (" << size << "/" << capacity << ")" << std::endl;
    }

    [[nodiscard]] int top() const
    {
        return size > 0 ? tab[size - 1] : -1;
    }

    int pop()
    {
        if (size == 0) return -1;
        int ret = tab[--size];
        std::cout << "popped from stack (" << size << "/" << capacity << ")" << std::endl;
        return ret;
    }

    [[nodiscard]] bool empty() const
    {
        return size == 0;
    }

    [[nodiscard]] int full() const
    {
        return size == capacity;
    }
};

DynamicStack drain(DynamicStack s)
{
    while (!s.empty())
    {
        s.pop();
    }

    return s;
}

DynamicStack make_stack(int capacity, int size) {
    DynamicStack s(capacity);
    for (int i = 0; i < size; ++i) {
        s.push(i);
    }
    return s;
}

DynamicStack pass(DynamicStack s) { return s; }

int main()
{
    {
        std::cout << "[1] init from temporary" << std::endl;
        DynamicStack s = DynamicStack{3};
    }

    {
        std::cout << "[2] forward temporary via pass()" << std::endl;
        DynamicStack s = pass(DynamicStack{3});
    }

    {
        std::cout << "[3] move construction" << std::endl;
        DynamicStack s = make_stack(3, 2);
        DynamicStack copy(std::move(s)); // DynamicStack s3 = std::move(s);
    }

    {

        std::cout << "[4] move assignment" << std::endl;
        DynamicStack s = make_stack(3, 2);
        DynamicStack other;
        other = std::move(s);
    }

    {
        std::cout << "[5] pass through function" << std::endl;
        DynamicStack s;
        s = drain(make_stack(5, 2));
    }

    return 0;
}
