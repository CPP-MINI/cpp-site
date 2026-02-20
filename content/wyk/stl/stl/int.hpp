#ifndef INT_HPP
#define INT_HPP

#include <iostream>

class A {
public:
    A() { std::cout << "A()\n"; }
    A(const A&) { std::cout << "A(const A&)\n"; }
    A(A&&) { std::cout << "A(A&&)\n"; }
    ~A() { std::cout << "~A()\n"; }
    A& operator=(const A&) { std::cout << "A::operator=(const A&)\n"; return *this; }
    A& operator=(A&&) { std::cout << "A::operator=(A&&)\n"; return *this; }
};

class B {
   public:
    B() { std::cout << "B()\n"; }
    B(const B&) { std::cout << "B(const B&)\n"; }
    B(B&&) { std::cout << "B(B&&)\n"; }
    ~B() { std::cout << "~B()\n"; }
    B& operator=(const B&) { std::cout << "B::operator=(const B&)\n"; return *this; }
    B& operator=(B&&) { std::cout << "B::operator=(B&&)\n"; return *this; }
};

class Int
{
    int val;
public:
    Int(int val) : val{val} { std::cout << "Int()" << " val = " << val << "\n"; }
    Int(const Int& i) : val{i.val} { std::cout << "Int(const Int&)" << " val = " << val << "\n"; }
    Int(Int&& i): val{i.val} { std::cout << "Int(Int&&)" << " val = " << val << "\n"; }
    Int& operator=(const Int& i) { val = i.val; std::cout << "Int& operator=(const Int&)" << " val = " << val << "\n"; return *this; }
    Int& operator=(Int&& i) {  val = i.val; std::cout << "Int& operator=(Int&&)" << " val = " << val << "\n"; return *this; }
    ~Int() { std::cout << "~Int()" << " val = " << val << "\n"; }
};

#endif
