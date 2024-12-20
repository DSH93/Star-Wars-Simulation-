#include "model/SpaceStation.h"


SpaceStation::SpaceStation(int crystalsAmount, int productionRate, Position position, const std::string &identifier)
        : SpaceObject(position, identifier), crystalsAmount(crystalsAmount), productionRate(productionRate) {}


void SpaceStation::printDockingShuttles() {
    if (!dockingShuttles.empty()) {
        std::cout << "Docking shuttles:" << std::endl;
        for (const auto &shuttle : dockingShuttles) {
            std::cout << "  - " << shuttle->getId() << std::endl;
        }
    }
}


void SpaceStation::status() {
    std::cout << "Station " << id << ", at " << position.toString()
              << "Inventory: " << crystalsAmount << " crystals\n"
              << "Production Rate: " << productionRate << "\n"
              << "Number of Docking Shuttles: " << dockingShuttles.size()
              << std::endl;
    printDockingShuttles();

}


std::vector<std::shared_ptr<SpaceObject>> SpaceStation::filterDockingShuttles() {
    std::vector<std::shared_ptr<SpaceObject>> updatedShuttles;
    for (const auto &shuttle : dockingShuttles) {
        if (shuttle->getCurrentPosition() == position) {
            updatedShuttles.push_back(shuttle);
        }
    }
    return updatedShuttles;
}


void SpaceStation::update() {
    if (!dockingShuttles.empty()) {
        dockingShuttles = filterDockingShuttles();
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

