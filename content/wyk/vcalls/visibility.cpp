class Base
{
private:
    int x = 1;

protected:
    int y = 2;

public:
    int z = 3;
};

class DerivedPublic : public Base
{
public:
    void foo()
    {
        // x *= 2;
        y *= 2;
        z *= 2;
    }
};

class DerivedPrivate : private Base
{
public:
    void foo()
    {
        // x *= 2;
        y *= 2;
        z *= 2;
    }
};

class DerivedProtected : protected Base
{
public:
    void foo()
    {
        // x *= 2;
        y *= 2;
        z *= 2;
    }
};

int main()
{
    DerivedPublic pub;
    // pub.x *= 2;
    // pub.y *= 2;
    pub.z *= 2;

    DerivedPrivate priv;
    // priv.x *= 2;
    // priv.y *= 2;
    // priv.z *= 2;

    DerivedProtected prot;
    prot.x *= 2;
    prot.y *= 2;
    prot.z *= 2;

    return 0;
}
