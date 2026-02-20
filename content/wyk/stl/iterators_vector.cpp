#include <memory>
#include <iostream>

class vector {
    std::unique_ptr<int[]> _data;
    std::size_t _capacity;
    std::size_t _size;
  public:
    vector() : _data(std::make_unique<int[]>(4)), _capacity(4), _size(0) {}

    int& operator[](std::size_t index) {
        return _data[index];
    }

    const int& operator[](std::size_t index) const {
        return _data[index];
    }

    std::size_t size() const { return _size; }

    void push_back(int value) {
        if (_size == _capacity) {
            std::unique_ptr<int[]> data = std::make_unique<int[]>(_capacity * 2);
            for (int i = 0; i < _size; ++i) {
                data[i] = this->_data[i];
            }
            this->_data = std::move(data);
            _capacity *= 2;
        }
        this->_data[_size++] = value;
    }

    class iterator {
        int* ptr;
    public:
        iterator(int* ptr) : ptr(ptr) {}

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        int& operator*() { return *ptr; }

        bool operator==(const iterator& other) { return ptr == other.ptr; }
        bool operator!=(const iterator& other) { return !(*this == other); }
    };

    iterator begin() { return iterator(_data.get()); }
    iterator end() { return iterator(_data.get() + _size); }


    class const_iterator {
        const int* ptr;
    public:
        const_iterator(const int* ptr) : ptr(ptr) {}

        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const int& operator*() { return *ptr; }

        bool operator==(const const_iterator& other) { return ptr == other.ptr; }
        bool operator!=(const const_iterator& other) { return !(*this == other); }
    };

    const_iterator cbegin() const { return const_iterator(_data.get()); }
    const_iterator cend() const { return const_iterator(_data.get() + _size); }

    const_iterator begin() const { return cbegin(); }
    const_iterator end() const { return cend(); }
};

void print(const vector& v) {
    for (vector::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    vector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for (vector::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
        *it *= 2;
    }
    std::cout << std::endl;

    print(v);
    return 0;
}

