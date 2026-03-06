#include <iostream>
#include <string>

struct Point {
    int x, y;
};

class Ptr
{
    Point* _ptr;
   public:
    Ptr(Point* ptr) : _ptr(ptr) {}
    ~Ptr() { delete _ptr; }
    Point* operator->() { return _ptr; }
    Point& operator*() { return *_ptr; }
};

int main()
{
    Ptr p(new Point{1, 2});
    p->x = 3;
    *p = {3, 4};
    return 0;
}
