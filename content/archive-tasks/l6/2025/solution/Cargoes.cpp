#include "Cargoes.hpp"

// Cargo
uint64_t Cargo::cargoIDCounter = 0;

// RawMaterialCargo
RawMaterialCargo::RawMaterialCargo(const std::string& name, double weight, double purity)
    : Cargo(name), purityPercentage(purity), weight(weight) {
}

std::string RawMaterialCargo::getDescription() const {
    return name + " (ID: " + std::to_string(cargoID) + ") - Raw Material: Purity " + std::to_string(purityPercentage) + "%";
}

double RawMaterialCargo::getWeight() const {
    return weight;
}

// ManufacturedGoodsCargo
ManufacturedGoodsCargo::ManufacturedGoodsCargo(const std::string& name, unsigned int count, double weightPU)
    : Cargo(name), unitCount(count), weightPerUnit(weightPU) {
}

std::string ManufacturedGoodsCargo::getDescription() const {
    return name + " (ID: " + std::to_string(cargoID) + ") - Manufactured Goods: " + std::to_string(unitCount) + " units";
}

double ManufacturedGoodsCargo::getWeight() const {
    return unitCount * weightPerUnit;
}

// HazardousWasteCargo
HazardousWasteCargo::HazardousWasteCargo(const std::string& name, double weight, DangerLevel danger)
    : Cargo(name), dangerLevel(danger), weight(weight) {
}

std::string HazardousWasteCargo::getDescription() const {
    std::string levelStr;
    switch (dangerLevel) {
    case DangerLevel::LOW: levelStr = "Low"; break;
    case DangerLevel::MEDIUM: levelStr = "Medium"; break;
    case DangerLevel::HIGH: levelStr = "High"; break;
    case DangerLevel::CRITICAL: levelStr = "CRITICAL"; break;
    }
    return name + " (ID: " + std::to_string(cargoID) + ") - Hazardous Waste: Danger Level " + levelStr;
}

double HazardousWasteCargo::getWeight() const {
    return weight;
}