#include <variant>

int main() {
    std::variant<int, float, bool> v;
    v = 3;
    v = 2.0f;
    v = true;

    if (std::holds_alternative<bool>(v)) {
        std::get<bool>(v) = false;
    }

    return 0;
}
