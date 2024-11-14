//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/StarDestroyer.h"
#include <algorithm>


void StarDestroyer::interact(std::shared_ptr<SpaceObject> other) {
    // empty implementation

}

void StarDestroyer::addMission() {
    // empty implementation

}

void StarDestroyer::status() {
    std::cout << "Star Destroyer " << id << " at " << position << " ";

}

void StarDestroyer::update() {
    position = getCurrentPosition();

}


void StarDestroyer::startMission() {
    // empty implementation


}

void StarDestroyer::finishMission() {
    // empty implementation


}

std::string StarDestroyer::createMissile(Position targetPos) {
    std::string missileName = "m" + std::to_string(missilesCounter);
    auto missile = std::make_shared<Missile>(position, targetPos, missileName);
    missilesMap[missileName] = std::move(missile);
    bomberMissiles.push_back(missileName);
    return missileName;

}

std::string StarDestroyer::missileUpdate(const std::vector<std::pair<std::string, Position>> &falconsPositions) {
    std::string falconName;
    for (const auto& missileName: bomberMissiles) {
        auto missile = std::dynamic_pointer_cast<Missile>(missilesMap[missileName]);
        falconName = missile->update(falconsPositions); // if missile hit falcon return falcon name
        if (missile->isMissileDestroyed()) {
            std::cout << "Missile " << getId() << " hits Falcon " << falconName << "at " << missile->getTarget() << std::endl;
            // remove missile from the map
            missilesMap.erase(missileName);
            // remove missile from the vector
            bomberMissiles.erase(std::remove(bomberMissiles.begin(), bomberMissiles.end(), missileName),bomberMissiles.end());

        }
    }
    return falconName;
}



void StarDestroyer::shoot(Position targetPos) {
    missilesCounter++;
    std::string missileName = createMissile(targetPos);
    std::cout << "TIE Bomber " << id << " shoot missile " << missileName << " to " << targetPos << std::endl;

}
