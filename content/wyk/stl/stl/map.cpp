#include <iostream>
#include <map>

struct color
{
    int r, g, b;

    color() : r(0), g(0), b(0) { std::cout << "color()" << std::endl; }

    color(int r, int g, int b) : r(r), g(g), b(b)
    {
        std::cout << "color(" << r << ", " << g << ", " << b << ")" << std::endl;
    }

    ~color() { std::cout << "~color() (" << r << ", " << g << ", " << b << ")" << std::endl; }

    color(const color& c) : r(c.r), g(c.g), b(c.b)
    {
        std::cout << "color(const color &c) (" << r << ", " << g << ", " << b << ")" << std::endl;
    }

    color(color&& c) noexcept : r(c.r), g(c.g), b(c.b)
    {
        std::cout << "color(color &&c) (" << r << ", " << g << ", " << b << ")" << std::endl;
    }

    color& operator=(const color& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        std::cout << "color &operator=(const color &c) (" << r << ", " << g << ", " << b << ")" << std::endl;
        return *this;
    }

    color& operator=(color&& c) noexcept
    {
        r = c.r;
        g = c.g;
        b = c.b;
        std::cout << "color &operator=(color &&c) (" << r << ", " << g << ", " << b << ")" << std::endl;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, const color& c)
{
    os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}

int main()
{
    std::map<std::string, color> colors = {
        {"red", color{255, 0, 0}}, {"green", color{0, 255, 0}}, {"blue", color{0, 0, 255}}};

    std::cout << "iterating" << std::endl;
    std::cout << "  colors.size() = " << colors.size() << std::endl;
    for (auto it = colors.begin(); it != colors.end(); ++it)
    {
        std::cout << "  colors[" << it->first << "] = " << it->second << std::endl;
    }

    std::cout << "insert black" << std::endl;
    colors.insert(std::make_pair("black", color{0, 0, 0}));

    std::cout << "iterating" << std::endl;
    std::cout << "  colors.size() = " << colors.size() << std::endl;
    for (const auto& [key, value] : colors)
    {
        std::cout << "  colors[" << key << "] = " << value << std::endl;
    }

    auto it = colors.find("black");
    if (it != colors.end())
    {
        std::cout << "Found colors[" << it->first << "] = " << it->second << std::endl;
    }

    std::cout << "  colors[blue] = color{0, 0, 255}" << std::endl;
    colors["blue"] = color{0, 0, 254};
    std::cout << "  colors[magenta] = color{0, 0, 255}" << std::endl;
    colors["magenta"] = color{255, 0, 255};

    std::cout << "clearing" << std::endl;
    colors.clear();
    std::cout << "  colors.size() = " << colors.size() << std::endl;

    return 0;
}
