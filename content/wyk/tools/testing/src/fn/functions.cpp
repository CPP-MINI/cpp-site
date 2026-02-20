#include "functions.hpp"

#include <cstring>

namespace functions {

long long fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

namespace {
    char* internal_strdup(const char* s) {
        char* ret = new char[std::strlen(s) + 1];
        for (int i = 0; i < std::strlen(s); ++i) {
            ret[i] = s[i];
        }
        return ret;
    }
}

string::string() : _data(new char[1]{0}), _size(0) {}

string::string(const char* s) : _data(internal_strdup(s)), _size(std::strlen(s)) {}

string::string(const string& s) : _data(internal_strdup(s._data)), _size(s._size) {}

string::string(string&& s) : _data(s._data), _size(s._size) {
    s._data = nullptr;
    s._size = 0;
}

string::~string() {
    if (_data) delete[] _data;
}

string& string::operator=(const string& s) {
    if (this == &s) return *this;
    char* copy = internal_strdup(s._data);
    if (_data) delete[] _data;
    _data = copy;
    _size = s._size;
    return *this;
}

string& string::operator=(string&& s) {
    if (this == &s) return *this;
    if (_data) delete[] _data;
    _data = s._data;
    _size = s._size;
    s._data = nullptr;
    s._size = 0;
    return *this;
}

string& string::append(const char* s) {
    std::size_t new_size = _size + std::strlen(s);
    char* new_data = new char[new_size + 1];
    std::memcpy(new_data, _data, _size);
    std::memcpy(new_data + _size, s, std::strlen(s));
    delete[] _data;
    _data = new_data;
    _size = new_size;
    _data[_size] = 0;
    return *this;
}

string& string::append(const string& s) {
    return append(s._data);
}

}