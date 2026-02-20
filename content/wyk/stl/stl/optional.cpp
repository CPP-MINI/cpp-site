#include <optional>

#include "int.hpp"

int main() {
    std::optional<A> null;
    std::optional<A> null2 = std::nullopt;

    {
        A a;
        std::optional<A> opt(a);
        opt = null;
    }

    {
        std::optional<A> opt{A()};
        if (opt.has_value()) {
            *opt = A();
            opt.value() = A();
        }
        opt.reset();
    }

    return 0;
}
