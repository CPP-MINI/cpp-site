#include <iostream>
#include <vector>
#include <string>

#define STAGE_1
#define STAGE_2
#define STAGE_3
#define STAGE_4

// TODO: Include all necessary headers
#include "Cargoes.hpp"
#include "TransportVessels.hpp"
#include "LogisticsReport.hpp"

int main() {
	std::cout << "--- Galactic Trade Federation - Interstellar Logistics ---" << std::endl;

#ifdef STAGE_1
	std::cout << "\n--- Stage 1: Cargo ---" << std::endl;
	std::vector<Cargo*> cargoInventory;
	cargoInventory.push_back(new RawMaterialCargo("Unrefined Spicestone", 500.0, 95.5));
	cargoInventory.push_back(new ManufacturedGoodsCargo("Xenon Blasters", 10, 25.0));
	cargoInventory.push_back(new RawMaterialCargo("Gaseous Helium-3", 150.0, 99.0));
	cargoInventory.push_back(new ManufacturedGoodsCargo("Medical Droids", 2, 75.0));
	cargoInventory.push_back(new ManufacturedGoodsCargo("Live Xenoflora Specimen", 1, 15.0));
	cargoInventory.push_back(new RawMaterialCargo("Synthetic Nutrient Paste (Bulk)", 800.0, 100.0));
	cargoInventory.push_back(new ManufacturedGoodsCargo("Cryogenic Data Core", 1, 0.5));
	cargoInventory.push_back(new ManufacturedGoodsCargo("Pre-Fabricated Colony Modules", 4, 5000.0));
	cargoInventory.push_back(new ManufacturedGoodsCargo("Ancient Alien Artifact", 1, 10.0));

	for (auto cargo : cargoInventory) {
		std::cout << " --------- " << cargo->getName() << " (" << cargo->getID() << ") ---------" << std::endl;
		std::cout << "\tWeight: " << cargo->getWeight() << std::endl;
		std::cout << "\tDescription: " << cargo->getDescription() << std::endl;
	}
#endif // STAGE_1

#ifdef STAGE_2
	std::cout << "\n--- Stage 2: Transport Vessels ---" << std::endl;
	std::vector<TransportVessel*> vesselFleet;
	vesselFleet.push_back(new Freighter("GTF-FR-Alpha-001", 1000.0));
	vesselFleet.push_back(new ScoutShip("GTF-SC-Beta-002", 75.0));
	vesselFleet.push_back(new ScoutShip("GTF-PD-Epsilon-004", 1500.0));
	vesselFleet.push_back(new Freighter("GTF-MF-Eta-006", 100.0));

	std::cout << "Loading vessels with cargo:" << std::endl;
	vesselFleet[0]->loadCargo(cargoInventory[0]);
	vesselFleet[0]->loadCargo(cargoInventory[1]);
	vesselFleet[0]->loadCargo(cargoInventory[2]);
	vesselFleet[0]->loadCargo(cargoInventory[3]);

	vesselFleet[2]->loadCargo(cargoInventory[4]);
	vesselFleet[2]->loadCargo(cargoInventory[5]);

	vesselFleet[3]->loadCargo(cargoInventory[6]);
	vesselFleet[3]->loadCargo(cargoInventory[7]);
	vesselFleet[3]->loadCargo(cargoInventory[8]);

	std::cout << "\nVessels:" << std::endl;
	for (auto vessel : vesselFleet) {
		std::cout << "ID: " << vessel->getID() << std::endl;
		std::cout << "\tLoad: " << vessel->getCurrentLoad() << "/" << vessel->getMaxCapacity() << std::endl;
		std::cout << "\tCargo count: " << vessel->getLoadedCargo().size() << std::endl;
	}
#endif // STAGE_2

#ifdef STAGE_3
	std::cout << "\n--- Stage 3: Hazardous Waste ---" << std::endl;
	size_t start = cargoInventory.size();
	cargoInventory.push_back(new HazardousWasteCargo("Corrosive Sludge", 100.0, DangerLevel::HIGH));
	cargoInventory.push_back(new HazardousWasteCargo("Defective Gravitron Flux Capacitors", 120.0, DangerLevel::LOW));
	cargoInventory.push_back(new HazardousWasteCargo("Stabilized Antimatter Rods", 250.0, DangerLevel::CRITICAL));
	std::cout << "New Hazardous Waste Cargo:\n";
	for (size_t i = start; i < cargoInventory.size(); i++) {
		auto cargo = cargoInventory[i];
		std::cout << " --------- " << cargo->getName() << " (" << cargo->getID() << ") ---------" << std::endl;
		std::cout << "\tWeight: " << cargo->getWeight() << std::endl;
		std::cout << "\tDescription: " << cargo->getDescription() << std::endl;
	}

	std::cout << "\nLoading hazardous waste:\n";
	std::cout << "Result: " << (vesselFleet[2]->loadCargo(cargoInventory[start]) == false ? "OK" : "WRONG!") << std::endl;
	std::cout << "Result: " << (vesselFleet[0]->loadCargo(cargoInventory[start]) == true ? "OK" : "WRONG!") << std::endl;
	std::cout << "Result: " << (vesselFleet[2]->loadCargo(cargoInventory[start + 1]) == true ? "OK" : "WRONG!") << std::endl;
	std::cout << "Result: " << (vesselFleet[2]->loadCargo(cargoInventory[start + 2]) == false ? "OK" : "WRONG!") << std::endl;

#endif // STAGE_3

#ifdef STAGE_4
	std::cout << "\n--- Stage 4: Logistics Reporting ---" << std::endl;
	generateLogisticsReport(vesselFleet);
#endif // STAGE_4

	std::cout << "\n--- Cleaning up resources ---" << std::endl;
#ifdef STAGE_1
	for (Cargo* c : cargoInventory) { delete c; }
#endif // STAGE_1
#ifdef STAGE_2
	for (TransportVessel* v : vesselFleet) { delete v; }
#endif // STAGE_2
	return 0;
}