#include <memory>

template<typename T>
class vector {
    std::unique_ptr<T[]> data;
    std::size_t capacity;
    std::size_t size;

public:
    vector() : data{std::make_unique<T[]>(4)}, capacity{4}, size{0} {}

    void push_back(const T& val) {
        if (size == capacity) {
            auto buffer = std::make_unique<T[]>(capacity * 2);
            for (std::size_t i = 0; i < size; ++i) {
                buffer[i] = data[i];
            }
            data = std::move(buffer);
            capacity *= 2;
        }
        data[size++] = val;
    }
};

template<typename T, typename U>
class pair {
    T t;
    U u;
public:
    pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}
    T& first() { return t; }
    U& second() { return u; }
    const T& first() const { return t; }
    const U& second() const { return u; }
};

template<typename T>
void swap(T& a, T& b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template<typename T, typename U>
pair<T, U> make_pair(const T& t, const U& u) {
    return pair<T, U>(t, u);
}

template<typename T, typename U>
pair<U, T> swap(const pair<T, U>& a) {
    return make_pair(a.second(), a.first());
}

int main() {
    vector<int> v;     // vector<int> to już poprawny typ
    vector<float> fv;

    v.push_back(1);
    fv.push_back(1.0);

    pair<int, float> p(1, 1.0);
    p.first() = 2;
    p.second() = 2.0;

    int i = 10;
    swap(i, p.first());

    pair<float, int> p2 = swap(p);

    return 0;
}