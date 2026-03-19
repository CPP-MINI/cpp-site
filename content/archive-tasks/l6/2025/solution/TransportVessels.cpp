#include "TransportVessels.hpp"

#include <iostream>
#include <algorithm>

// Freighter
bool Freighter::loadCargo(Cargo* cargo) {
	if (currentLoad + cargo->getWeight() <= maxCapacity) {
		loadedCargo.push_back(cargo);
		currentLoad += cargo->getWeight();

		// Stage 3: Dynamic Casting for HazardousWasteCargo
		if (HazardousWasteCargo* hwCargo = dynamic_cast<HazardousWasteCargo*>(cargo)) {
			std::cout << "  WARNING: Hazardous Waste Cargo (" << hwCargo->getName()
				<< ", Danger Level: " << static_cast<int>(hwCargo->getDangerLevel()) << ") loaded!" << std::endl;
		}

		std::cout << getID() << " loaded " << cargo->getDescription()
			<< ". Current load: " << currentLoad << " / " << maxCapacity << std::endl;
		return true;
	}

	std::cout << getID() << " cannot load " << cargo->getDescription()
		<< ". Exceeds capacity of " << maxCapacity << " units." << std::endl;
	return false;
}

double Freighter::getMaxCapacity() const {
	return maxCapacity;
}

// ScoutShip
bool ScoutShip::loadCargo(Cargo* cargo) {
	const double maxCargoWeight = 200.0;
	if (cargo->getWeight() <= maxCargoWeight && currentLoad + cargo->getWeight() <= maxCapacity) {
		loadedCargo.push_back(cargo);
		currentLoad += cargo->getWeight();

		// Stage 3: Dynamic Casting for HazardousWasteCargo
		if (HazardousWasteCargo* hwCargo = dynamic_cast<HazardousWasteCargo*>(cargo)) {
			if (hwCargo->getDangerLevel() != DangerLevel::LOW) {
				std::cout << getID() << " cannot load " << cargo->getDescription()
					<< ". Too dangerous to ship!" << std::endl;
				return false;
			}
			std::cout << "  WARNING: Hazardous Waste Cargo (" << hwCargo->getName()
				<< ", Danger Level: " << static_cast<int>(hwCargo->getDangerLevel()) << ") loaded!" << std::endl;
		}

		std::cout << getID() << " loaded " << cargo->getDescription()
			<< ". Current load: " << currentLoad << " / " << maxCapacity << std::endl;
		return true;
	}

	std::cout << getID() << " cannot load " << cargo->getDescription()
		<< ". Exceeds capacity of " << maxCapacity << " units." << std::endl;
	return false;
}

double ScoutShip::getMaxCapacity() const {
	return maxCapacity;
}