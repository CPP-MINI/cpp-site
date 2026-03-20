#include "SensorCollection.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>

void SensorCollection::addSensor(const std::string& type, const Sensor<double>& sensor) {
    sensorsByType[type].push_back(sensor);
}

const std::unordered_map<std::string, std::list<Sensor<double>>>& SensorCollection::getSensorsByType() const {
    return sensorsByType;
}

std::list<Sensor<double>> SensorCollection::getAllSensors() const {
    std::list<Sensor<double>> all;
    for (const auto& [_, lst] : sensorsByType) {
        all.insert(all.end(), lst.begin(), lst.end());
    }
    return all;
}

void SensorCollection::reverseSensors() {
    for (auto& [_, lst] : sensorsByType) {
        lst.reverse();
    }
}

void SensorCollection::removeShortSensors(const std::string& type, std::size_t minCount) {
    auto it = sensorsByType.find(type);
    if (it != sensorsByType.end()) {
        it->second.remove_if([&](const auto& s) {
            return s.getMeasurements().size() < minCount;
            });
    }
}

double SensorCollection::getTotalMinSum() const {
    auto all = getAllSensors();
    return std::accumulate(all.begin(), all.end(), 0.0, [](double sum, const auto& s) {
        return sum + s.getMin();
        });
}

std::vector<Sensor<double>> SensorCollection::getSensorsContaining(const std::string& keyword) const {
    auto all = getAllSensors();
    std::vector<Sensor<double>> result;
    std::copy_if(all.begin(), all.end(), std::back_inserter(result), [&](const Sensor<double>& s) {
        return s.getLabel().find(keyword) != std::string::npos;
        });
    return result;
}

std::optional<Sensor<double>> SensorCollection::findHighestRMS() const {
    auto all = getAllSensors();
    if (all.empty()) return std::nullopt;
    return *std::max_element(all.begin(), all.end(), [](const auto& a, const auto& b) {
        return a.getRMS() < b.getRMS();
        });
}

std::ostream& SensorCollection::writeToStream(std::ostream& os) const
{
    for (const auto& [type, lst] : sensorsByType) {
        os << "=== " << type << " ===\n";
        for (const auto& s : lst) {
            os << s;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const SensorCollection& c) {
    return c.writeToStream(os);
}
