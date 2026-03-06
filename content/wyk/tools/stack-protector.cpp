#include <iostream>
#include <cstring>

int main() {
    char cmd[10];
    int x, y;
    std::cin >> x >> cmd >> y;
    int result;
    if (std::strcmp(cmd, "+") == 0) {
        result = x + y;
    } else if (std::strcmp(cmd, "-") == 0) {
        result = x - y;
    }
    std::cout << x << " " << cmd << " " << y << " = " << result << std::endl;
    return 0;
}
