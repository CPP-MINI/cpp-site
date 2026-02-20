class A
{
    int val;

public:
    A(int x) : val(x)
    {
    }
};

// A ga;
A ga(3);

int main()
{
    // A a;
    A a(3);

    // A* pa = new A;
    A* pa = new A(3);

    return 0;
}
