#include <iostream>

class AbstractArray
{
   public:
    // virtual ~AbstractArray() = default;
    virtual std::size_t size() const = 0;
    virtual int get(std::size_t idx) const = 0;
};

class FakeArray : public AbstractArray
{
    std::size_t _size;

   public:
    FakeArray(std::size_t size) : _size(size) {}
    std::size_t size() const override { return _size; }
    int get(std::size_t idx) const override { return idx; }
};

class HeapArray : public AbstractArray
{
    std::size_t _size;
    int* _data;

   public:
    HeapArray(std::size_t size) : _size(size), _data(new int[size])
    {
        for (std::size_t i = 0; i < size; i++)
            _data[i] = i;
    }

    ~HeapArray()
    {
        delete[] _data;
    }

    std::size_t size() const override { return _size; }
    int get(std::size_t idx) const override { return _data[idx]; }
};

int main()
{
    AbstractArray* arrays[] = {new FakeArray(10), new HeapArray(10)};

    for (auto ptr : arrays)
    {
        const AbstractArray& arr = *ptr;
        for (std::size_t i = 0; i < arr.size(); i++)
        {
            std::cout << arr.get(i) << ", ";
        }
        std::cout << std::endl;
    }

    for (auto array : arrays)
        delete array;

    return 0;
}
