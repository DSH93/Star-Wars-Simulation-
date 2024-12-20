#include "model/spaceships/StarDestroyer.h"
#include <algorithm>

StarDestroyer::StarDestroyer(const Position& pos, const std::string& identifier, float speed, const std::shared_ptr<Admiral>& pilot, const std::vector<std::shared_ptr<SpaceObject>>& sites)
        : Spaceship(pos, identifier, sites), pilot(pilot) {
    if (!pilot) {
        throw std::invalid_argument("Pilot cannot be null");
    }
    this->setSpeed(speed);
    logCreation("Star Destroyer", identifier, speed);
}



void StarDestroyer::status() {
    Spaceship::status();
    for (const auto& missileName: destroyerMissiles) {
        auto missile = std::dynamic_pointer_cast<Missile>(missilesMap[missileName]);
        missile->status();
    }

}



std::string StarDestroyer::createMissile(Position targetPos) {
    std::string missileName = "m" + std::to_string(missilesCounter);
    auto missile = std::make_shared<Missile>(position, targetPos, missileName, sites);
    missilesMap[missileName] = std::move(missile);
    destroyerMissiles.push_back(missileName);
    return missileName;

}

std::string StarDestroyer::missileUpdate(const std::vector<std::pair<std::string, Position>> &falconsPositions) {
    std::string falconName;
    for (const auto& missileName: destroyerMissiles) {
        auto missile = std::dynamic_pointer_cast<Missile>(missilesMap[missileName]);
        falconName = missile->updateAndCheckTarget(falconsPositions); // if missile hit falcon return falcon name
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

std::vector<std::pair<std::string, Position>> StarDestroyer::getMissilesNameAndPosition() {
    std::vector<std::pair<std::string, Position>> missiles;
    for (const auto& missileName: destroyerMissiles) {
        auto missile = std::dynamic_pointer_cast<Missile>(missilesMap[missileName]);
        missiles.emplace_back(missileName, missile->getPosition());
    }
    return missiles;
}


