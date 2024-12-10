//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/SpaceStation.h"

// SpaceStation(int crystalsAmount, int productionRate, Position position, std::string identifier);


SpaceStation::SpaceStation(int crystalsAmount, int productionRate, Position position, std::string identifier)
    : SpaceObject(position, identifier),  crystalsAmount(crystalsAmount), productionRate(productionRate) {}


int SpaceStation::getCrystalsAmount() const {
    return crystalsAmount;
}


void SpaceStation::status() {
    std::cout << "Station " << id << ", at " << "Position: (" << position.getX() << ", " << position.getY() << "), Inventory: "
    << crystalsAmount  << std::endl;
}


void SpaceStation::update() {
    crystalsAmount += productionRate;
}

Position SpaceStation::getCurrentPosition() {
    return position;
}

void SpaceStation::toString() const {
    std::cout << "SpaceStation: " << id << " at " << "Position: (" << position.getX() << ", " << position.getY() << ") with " << getCrystalsAmount() << " crystals and production rate of " << productionRate << std::endl;
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
    // Do nothing
}
