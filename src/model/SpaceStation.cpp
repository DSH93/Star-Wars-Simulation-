//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/SpaceStation.h"


SpaceStation::SpaceStation(int crystalsAmount, int productionRate, Position position, const std::string &identifier)
        : SpaceObject(position, identifier), crystalsAmount(crystalsAmount), productionRate(productionRate) {}


void SpaceStation::status() {
    std::cout << "Station " << id << ", at " << position.toString()
              << "Inventory: " << crystalsAmount << " crystals\n"
              << "Production Rate: " << productionRate << "\n"
              << "Number of Docking Shuttles: " << dockingShuttles.size()
              << std::endl;

    if (!dockingShuttles.empty()) {
        std::cout << "Docking shuttles:" << std::endl;
        for (const auto &shuttle : dockingShuttles) {
            std::cout << "  - " << shuttle->getId() << std::endl;
        }
    }

}


void SpaceStation::update() {
    if (!dockingShuttles.empty()) {
        std::vector<std::shared_ptr<SpaceObject>> updatedShuttles;
        for (const auto &shuttle: dockingShuttles) {
            if (shuttle->getCurrentPosition() == position) {
                updatedShuttles.push_back(shuttle);
            }
        }
        dockingShuttles = std::move(updatedShuttles);
    }
    crystalsAmount += productionRate;
}

Position SpaceStation::getCurrentPosition() {
    return position;
}

int SpaceStation::unloadCrystals() {
    int amount = 0;

    if (crystalsAmount > 5) {

        this->crystalsAmount = crystalsAmount - 5;
        amount = 5;

    } else {
        amount = crystalsAmount;
        this->crystalsAmount = 0;
    }

    std::cout << "Station " << id << " has unloaded " << amount << " crystals" << std::endl;
    return amount;

}

void SpaceStation::interact(std::shared_ptr<SpaceObject> other) {
    dockingShuttles.push_back(other);
}

