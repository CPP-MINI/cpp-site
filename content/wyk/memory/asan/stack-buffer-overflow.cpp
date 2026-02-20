#include <cstring>

int main() {
    char command[10];
    char output[250];
    std::strcpy(command, "/usr/bin/verylongcommand");
    std::strcpy(output, command);
    return 0;
}
