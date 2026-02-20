class A {
    int val;
public:
     A(int val = 0) : val{0}{}
};

class B {
    int val;
public:
    B(int val) : val{0}{}
};

class C {
    A a;
    B b;
    int val;
public:
     C(int a, int b, int c) : a{a}, b{b}, val{c}{}
     C(int b, int c) : b{b}, val{c}{} //!< ok bo A ma konstruktor domyślny
};

int main() {
    C obj(1, 2, 3);
    return 0;
};
