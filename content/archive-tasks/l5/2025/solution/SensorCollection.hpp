#pragma once

#include <unordered_map>
#include <list>
#include <optional>

#include "Sensor.hpp"

class SensorCollection {
private:
    std::unordered_map<std::string, std::list<Sensor<double>>> sensorsByType;

public:
    void addSensor(const std::string& type, const Sensor<double>& sensor);

    const std::unordered_map<std::string, std::list<Sensor<double>>>& getSensorsByType() const;
    std::list<Sensor<double>> getAllSensors() const;

    void reverseSensors();
    void removeShortSensors(const std::string& type, std::size_t minCount);

    double getTotalMinSum() const;

    std::vector<Sensor<double>> getSensorsContaining(const std::string& keyword) const;
    std::optional<Sensor<double>> findHighestRMS() const;

    std::ostream& writeToStream(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const SensorCollection& c);