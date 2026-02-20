#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cstddef>

namespace functions {

long long fib(int n);

class string {
private:
 char* _data;
 std::size_t _size;
 public:
  string();
  string(const char* s);
  string(const string& s);
  string(string&& s);
  ~string();

  char* data() { return _data; }
  const char* data() const { return _data; }

  std::size_t size() const { return _size; }
  std::size_t length() const { return _size; }

  string& operator=(const string& s);
  string& operator=(string&& s);

  string& append(const char* s);
  string& append(const string& s);
};

}

#endif
