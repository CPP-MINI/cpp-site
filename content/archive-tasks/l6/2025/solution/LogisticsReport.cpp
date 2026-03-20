#include "LogisticsReport.hpp"

#include <iostream>

void generateLogisticsReport(const std::vector<TransportVessel*>& allVessels) {
    std::cout << "\n--- Galactic Trade Federation Logistics Report ---" << std::endl;
    for (const auto& vessel : allVessels) 
    {
        std::cout << "- ID: " << vessel->getID() << ", Type: " << typeid(*vessel).name() << std::endl;
        std::cout << "     Current Load: " << vessel->getCurrentLoad() << " / " << vessel->getMaxCapacity() << std::endl;
        std::cout << "     Cargo Inventory:" << std::endl;
        int i = 1;
        for (const auto& cargo : vessel->getLoadedCargo())
        {
            std::cout << "     " << i++ << ". ID: " << cargo->getID() << ", Type: " << typeid(*cargo).name() << std::endl;
            std::cout << "        Desc: " << cargo->getDescription() << std::endl;
            if (const HazardousWasteCargo* hwCargo = dynamic_cast<const HazardousWasteCargo*>(cargo)) {
                std::cout << "        Danger Level: " << (int)hwCargo->getDangerLevel() << std::endl;
            }
        }
        if (i == 1) {
            std::cout << "        --- NONE ---" << std::endl;
        }
    }
    std::cout << "------------------------------------------------" << std::endl;
}