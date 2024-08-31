//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/SpaceStation.h"

// SpaceStation(int crystalsAmount, int productionRate, Position position, std::string identifier);


SpaceStation::SpaceStation(int crystalsAmount, int productionRate, Position position, std::string identifier)
    : SpaceObject(position, identifier),  crystalsAmount(crystalsAmount), productionRate(productionRate) {}



int SpaceStation::getCrystalsAmount() const {
    return 0;
}

void SpaceStation::setCrystalsAmount(int crystalsAmount) {
    // empty implementation
}

int SpaceStation::getProductionRate() const {
    return 0;
}

void SpaceStation::status() {
    // empty implementation
}

void SpaceStation::interact(std::shared_ptr<SpaceObject> other) {
    // empty implementation
}

void SpaceStation::update() {
    // empty implementation
}

Position SpaceStation::getCurrentPosition() {
    return Position(0, 0);
}

void SpaceStation::toString() const {
    std::cout << "SpaceStation: " << id << " at " << "Position: (" << position.getX() << ", " << position.getY() << ") with " << crystalsAmount << " crystals and production rate of " << productionRate << std::endl;
}
