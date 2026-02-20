#include <tuple>

int main() {
    std::tuple<int, float, bool> t = {1, 2.0, true};

    {
        int i = std::get<0>(t);
        float f = std::get<1>(t);
        bool b = std::get<2>(t);
    }

    t = std::make_tuple(0, 0.0, false);

    {
        auto [i, f, b] = t;
        auto& [ri, rf, rb] = t;
        ri = 2;
        rf = 4.0;
        rb = false;
    }

    return 0;
}
