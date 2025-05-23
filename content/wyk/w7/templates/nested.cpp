#include <iostream>
#include <string>

struct fake_string
{
    using value_type = char;
    using size_type = std::size_t;

    static const size_type npos = static_cast<size_type>(-1);

    size_type size() const
    {
        return 10;
    }

    value_type operator[](int i) const
    {
        return 'a' + i;
    }
};

template<typename StringType>
typename StringType::size_type find(const StringType& str, typename StringType::value_type c)
{
    for (typename StringType::size_type i = 0; i < str.size(); ++i)
    {
        if (c == str[i]) return i;
    }
    return StringType::npos;
}

int main()
{
    fake_string fs;
    std::string s("hello");

    std::cout << "find(fs, 'c') = " << find(fs, 'a') << std::endl;
    std::cout << "find(s, 'c') = " << find(s, 'a') << std::endl;

    return 0;
}
