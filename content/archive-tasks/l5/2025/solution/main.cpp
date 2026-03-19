#include <iostream>
#include <iomanip>

#include "Sensor.hpp"
#include "SensorCollection.hpp"

#define PART1
#define PART2
#define PART3
#define PART4

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // === Etap 1 ===
    std::cout << "*************** PART 1 (Basic Sensor) ***************\n\n";
#ifdef PART1
    Sensor<double>::Identity cpuID("CPU0", "thermal");
    Sensor<double> sensor1("CPU Load", cpuID, "%");
    Sensor<double> sensor2("RAM Usage", std::string("memory"));
    Sensor<double> sensor3("GPU Load", Sensor<double>::Identity("GPU0", "graphics"), "%");
    Sensor<double> sensor4("Fan Speed", "cooling", "RPM");

    std::cout << "Sensor1 info:\n";
    std::cout << "Label: " << sensor1.getLabel() << "\n";
    if (std::holds_alternative<Sensor<double>::Identity>(sensor1.getSource())) {
        const auto& src = std::get<Sensor<double>::Identity>(sensor1.getSource());
        std::cout << "Source: " << src.hardwareID << " (" << src.type << ")\n";
    }
    if (sensor1.getUnit()) {
        std::cout << "Unit: " << *sensor1.getUnit() << "\n";
    }

    std::cout << "\nSensor2 info:\n";
    std::cout << "Label: " << sensor2.getLabel() << "\n";
    if (std::holds_alternative<std::string>(sensor2.getSource())) {
        std::cout << "Source: " << std::get<std::string>(sensor2.getSource()) << "\n";
    }
#endif
    // === Etap 2 ===
    std::cout << "\n*************** PART 2 (Extended Sensor) ***************\n\n";
#ifdef PART2
    sensor1 << 45.5 << 72.0 << 33.5 << 50.0;
    sensor2 << 65.0 << 78.5;
    sensor3 << 90.0 << 88.5;

    std::cout << "\nSensor1 RMS: " << sensor1.getRMS() << ", Min: " << sensor1.getMin() << "\n";
    std::cout << "Sensor2 RMS: " << sensor2.getRMS() << ", Min: " << sensor2.getMin() << "\n";
    std::cout << "Sensor3 RMS: " << sensor3.getRMS() << ", Min: " << sensor3.getMin() << "\n";
    std::cout << "Sensor4 RMS: " << sensor4.getRMS() << ", Min: " << sensor4.getMin() << "\n";

    std::cout << "\n" << sensor1 << sensor2 << sensor3 << sensor4 << "\n";

    std::cout << "sensor1 != sensor2: " << (sensor1 != sensor2 ? "true" : "false") << "\n";
    std::cout << "sensor1 > sensor2: " << (sensor1 > sensor2 ? "true" : "false") << "\n";
    std::cout << "sensor3 > sensor1: " << (sensor3 > sensor1 ? "true" : "false") << "\n";
    std::cout << "sensor4 != sensor4: " << (sensor4 != sensor4 ? "true" : "false") << "\n";
#endif
    // === Etap 3 ===
    std::cout << "\n*************** PART 3 (SensorCollection) ***************\n\n";
#ifdef PART3
    SensorCollection collection;
    collection.addSensor("thermal", sensor1);
    collection.addSensor("memory", sensor2);
    collection.addSensor("graphics", sensor3);
    collection.addSensor("cooling", sensor4);
    collection.addSensor("thermal", Sensor<double>("Core Temp", Sensor<double>::Identity("CPU1", "thermal"), "°C") << 40.0 << 42.0);
    collection.addSensor("thermal", Sensor<double>("VRM Temp", "thermal", "°C") << 55.0);

    std::cout << "\nAll sensors in collection:\n";
    std::cout << collection;

    std::cout << "\nSensors in 'thermal':\n";
    for (const auto& s : collection.getSensorsByType().at("thermal")) {
        std::cout << s << "\n";
    }
#endif
    // === Etap 4 ===
    std::cout << "\n*************** PART 4 (Algorithms) ***************\n\n";
#ifdef PART4
    SensorCollection emptyCollection;
    collection.reverseSensors();
    collection.removeShortSensors("thermal", 2);
    collection.removeShortSensors("cooling", 1);

    double totalMin = collection.getTotalMinSum();
    std::cout << "\nTotal of minimum values across all sensors: " << totalMin << "\n";
    std::cout << "Total of minimum values across all sensors (empty collection): " << emptyCollection.getTotalMinSum() << "\n";

    std::cout << "\nSensors containing 'Temp':\n";
    for (const auto& s : collection.getSensorsContaining("Temp")) {
        std::cout << s << "\n";
    }
    std::cout << "Count of sensors containing 'RAM' (empty collection):" << emptyCollection.getSensorsContaining("RAM").size() << "\n";

    auto maybeSensor = collection.findHighestRMS();
    if (maybeSensor) {
        std::cout << "\n[OK] Sensor with highest RMS:\n" << *maybeSensor << "\n";
    }
    else {
        std::cout << "\n[ERROR] No sensors found.\n";
    }

    auto maybeSensor2 = emptyCollection.findHighestRMS();
    std::cout << "This should be std::nullopt: " << ((maybeSensor2 == std::nullopt) ? "OK" : "ERROR") << "\n";
#endif
    return 0;
}