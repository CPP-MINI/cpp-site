#include <vector>

class Stack
{
    int tab[10];
    int size;

public:
    Stack() : size(0)
    {
    }

    Stack(int single_elem) : size{1}, tab{single_elem, 0}
    {
    }

    Stack(const std::vector<int>& values) : size{static_cast<int>(values.size())}
    {
        for (std::size_t i = 0; i < values.size(); ++i)
        {
            tab[i] = values[i];
        }
    }

    Stack(int* values, int num) : size{num}
    {
        for (std::size_t i = 0; i < num; ++i)
        {
            tab[i] = values[i];
        }
    }

    void push(int val)
    {
        if (size == 10)
            return;
        tab[size++] = val;
    }

    [[nodiscard]] int top() const
    {
        return size > 0 ? tab[size - 1] : -1;
    }

    int pop()
    {
        if (size == 0)
            return -1;
        return tab[--size];
    }

    bool empty() const
    {
        return size == 0;
    }
};



int main()
{
    int arr[] = {1, 2, 3};
    std::vector<int> v{1, 2, 3};

    Stack s;
    Stack s2(1);
    Stack s3(arr, 3);
    Stack s4(v);

    Stack* ps = new Stack;
    Stack* ps2 = new Stack(1);
    Stack* ps3 = new Stack(arr, 3);
    Stack* ps4 = new Stack(v);

    return 0;
}