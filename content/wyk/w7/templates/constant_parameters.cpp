#include <iostream>

const char float_stack_name[] = "fstack";

template<typename T, std::size_t N, const char* NAME>
class stack
{
    T _data[N];
    std::size_t _size = 0;
public:
    void push(const T& value)
    {
        std::cout << "[" << NAME << "] push(" << value << ")" << std::endl;
        if (_size == N) throw std::overflow_error("stack overflow");
        _data[_size++] = value;
    }

    void pop()
    {
        std::cout << "[" << NAME << "] pop()" << std::endl;
        if (_size == 0) throw std::underflow_error("stack underflow");
        _size--;
    }

    T& top()
    {
        if (_size == 0) throw std::underflow_error("stack underflow");
        return _data[_size - 1];
    }
};

int main()
{
    stack<float, 10, float_stack_name> fstack;
    fstack.push(1.0);
    fstack.push(2.0);
    fstack.push(3.0);
    fstack.pop();
    return 0;
}
