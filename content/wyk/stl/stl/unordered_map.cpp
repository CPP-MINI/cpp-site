#include <iostream>
#include <unordered_map>

struct color
{
    int r, g, b;
    color() : r(0), g(0), b(0) {}
    color(int r, int g, int b) : r(r), g(g), b(b) {}

    bool operator==(const color& c) const {
        return r == c.r && g == c.g && b == c.b;
    }
};

std::ostream& operator<<(std::ostream& os, const color& c)
{
    os << "color(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}

struct color_hash {
    std::size_t operator()(const color& c) const {
        std::cout << "color_hash(" << c << ")" << std::endl;
        return (c.r << 16) ^ (c.g << 8) ^ c.b;
    }
};

int main()
{
    std::unordered_map<color, std::string, color_hash> color_names = {
        {color{255, 0, 0}, "red"}, {color{0, 255, 0}, "green", }, {color{0, 0, 255}, "blue"}};

    for (const auto& [color, name] : color_names) {
        std::cout << color << " -> " << name << std::endl;
    }

    auto it = color_names.find(color{255, 0, 0});
    if (it != color_names.end())
        std::cout << it->first << " -> " << it->second << std::endl;

    return 0;
}
