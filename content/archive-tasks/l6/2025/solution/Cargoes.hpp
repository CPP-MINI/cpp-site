#pragma once

#include <string>
#include <stdint.h>

class Cargo {
private:
	static uint64_t cargoIDCounter;

protected:
	uint64_t cargoID;
	std::string name;

public:
	Cargo(const std::string& name) : cargoID(++cargoIDCounter), name(name) {}
	virtual ~Cargo() = default;

	uint64_t getID() const { return cargoID; }
	const std::string& getName() const { return name; }

	virtual std::string getDescription() const = 0;
	virtual double getWeight() const = 0;
};


class RawMaterialCargo : public Cargo {
private:
	double purityPercentage;
	double weight;
public:
	RawMaterialCargo(const std::string& name, double weight, double purity);
	std::string getDescription() const override;
	double getWeight() const override;
};

class ManufacturedGoodsCargo : public Cargo {
private:
	unsigned int unitCount;
	double weightPerUnit;
public:
	ManufacturedGoodsCargo(const std::string& name, unsigned int count, double weightPU);
	std::string getDescription() const override;
	double getWeight() const override;
};

// Enum for HazardousWasteCargo danger levels
enum class DangerLevel {
	LOW = 0,
	MEDIUM = 1,
	HIGH = 2,
	CRITICAL = 3
};

class HazardousWasteCargo : public Cargo {
private:
	DangerLevel dangerLevel;
	double weight;
public:
	HazardousWasteCargo(const std::string& name, double weight, DangerLevel danger);
	std::string getDescription() const override;
	double getWeight() const override;
	DangerLevel getDangerLevel() const { return dangerLevel; }
};