#pragma once

#include <string>
#include <vector>

#include "Cargoes.hpp"

class TransportVessel {
protected:
    std::string vesselID;
    std::vector<Cargo*> loadedCargo;
    double currentLoad;
public:
    TransportVessel(const std::string& id) : vesselID(id), currentLoad(0.0) {}
    virtual ~TransportVessel() = default;

    virtual bool loadCargo(Cargo* cargo) = 0;
    virtual double getMaxCapacity() const { return -1; }
    double getCurrentLoad() const { return currentLoad; }

    std::string getID() const { return vesselID; }
    const std::vector<Cargo*>& getLoadedCargo() const { return loadedCargo; }
};

// Derived TransportVessel types

class Freighter : public TransportVessel {
private:
    double maxCapacity;
public:
    Freighter(const std::string& id, double capacity)
        : TransportVessel(id), maxCapacity(capacity) {
    }
    bool loadCargo(Cargo* cargo) override;
    double getMaxCapacity() const override;
};

class ScoutShip : public TransportVessel {
private:
    double maxCapacity;
public:
    ScoutShip(const std::string& id, double capacity)
        : TransportVessel(id), maxCapacity(capacity) {
    }
    bool loadCargo(Cargo* cargo) override;
    double getMaxCapacity() const override;
};

