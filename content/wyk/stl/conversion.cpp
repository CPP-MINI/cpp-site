#include <string>
#include <iostream>

#include <cstring>

class str {
    char* _data;
   public:
    /*explicit*/ str(const char* str) : _data{new char[std::strlen(str) + 1]} {
        std::memcpy(_data, str, std::strlen(str) + 1);
        std::cout << "str(\"" << _data << "\")\n";
    }

    str(const str& other) = delete;
    str& operator=(const str& other) = delete;

    ~str() {
        std::cout << "~str(\"" << _data << "\")\n";
        delete _data;
    }

    const char* data() const { return _data; }

    void append(const str& other) {
        std::size_t len = std::strlen(_data) + std::strlen(other._data) + 1;
        char* buffer = new char[len];
        std::memcpy(buffer, _data, std::strlen(_data));
        std::memcpy(buffer + std::strlen(_data), other._data, std::strlen(other._data));
        buffer[len - 1] = 0;
        delete _data;
        _data = buffer;
    }

    /*explicit*/ operator std::string() {
        return std::string(_data);
    }
};

void foo(str s) {
    std::cout << "foo(\"" << s.data() << "\")\n";
}

int main() {
    str s("hello");     // constructor converts const char* to str
    foo("hi");          // implicitly constructs temporary str("hi")
    s.append("world");  // implicitly constructs temporary str("world")

    std::string str = s;

    return 0;
}
