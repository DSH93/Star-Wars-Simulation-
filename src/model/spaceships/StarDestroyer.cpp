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
    std::cout << "Star Destroyer " << id << " at " << position << " , State: " << stateToString[state] << std::endl;
    for (const auto& missileName: destroyerMissiles) {
        auto missile = std::dynamic_pointer_cast<Missile>(missilesMap[missileName]);
        missile->status();
    }

}

void StarDestroyer::update() {
    position = getCurrentPosition();
    // todo make the updatemissle from update function


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
    destroyerMissiles.push_back(missileName);
    return missileName;

}

std::string StarDestroyer::missileUpdate(const std::vector<std::pair<std::string, Position>> &falconsPositions) {
    std::string falconName;
    for (const auto& missileName: destroyerMissiles) {
        auto missile = std::dynamic_pointer_cast<Missile>(missilesMap[missileName]);
        falconName = missile->update(falconsPositions); // if missile hit falcon return falcon name
        if (missile->isMissileDestroyed()) {
            std::cout << "Missile " << getId() << " hits Falcon " << falconName << "at " << missile->getTarget() << std::endl;
            // remove missile from the map
            missilesMap.erase(missileName);
            // remove missile from the vector
            destroyerMissiles.erase(std::remove(destroyerMissiles.begin(), destroyerMissiles.end(), missileName), destroyerMissiles.end());

        }
    }
    return falconName;
}



void StarDestroyer::shoot(Position targetPos) {
    missilesCounter++;
    std::string missileName = createMissile(targetPos);
    std::cout << "Destroyer " << id << " Shoot Missile [" << missileName << "] to " << targetPos << std::endl;

}
