#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class room {
    std::string _name;
public:
    room(std::string name) : _name {name} {}
    const std::string& name() {
        return _name;
    }
};

std::unique_ptr<room> make_room(int id) {
    return std::make_unique<room>("Room " + std::to_string(id));
}

int main() {
    std::vector<int> ids = {107, 218, 304, 318, 404};
    std::vector<std::unique_ptr<room>> rooms(ids.size());
    std::transform(ids.begin(), ids.end(), rooms.begin(), make_room);
    for (const auto& room_ptr : rooms) {
        std::cout << room_ptr->name() << std::endl;
    }
    return 0;
}
