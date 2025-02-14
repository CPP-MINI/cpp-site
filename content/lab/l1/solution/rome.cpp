#include "rome.hpp"

namespace rome {
    Province create_province(std::string name) {
        Province province;
        province.name = name;
        province.cities = {};
        return province;
    }

    void add_city(Province* province, std::string city) { province->cities.push_back(city); }

    std::string description(Province* province) {
        std::string concat = province->name + ": ";

        for (int i = 0; i < province->cities.size() - 1; ++i) {
            concat += province->cities[i] + ", ";
        }

        concat += province->cities[province->cities.size() - 1] + ".";

        return concat;
    }
}
