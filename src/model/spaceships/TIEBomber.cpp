//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/TIEBomber.h"
#include "model/spaceships/Missile.h"






void TIEBomber::update() {
    // empty implementation


}

void TIEBomber::status() {
    std::cout << "TIE Bomber " << id << " at " << position << std::endl;

}

void TIEBomber::randomPatrol() {
    // empty implementation

}

void TIEBomber::addPatrolMission() {
    // empty implementation

}

void TIEBomber::finishPatrolMission() {
    // empty implementation

}

Position TIEBomber::findClosestSpaceSite() {
    return Position(0, 0);     // empty implementation

}

void TIEBomber::flyToClosestSpaceSite() {
    // empty implementation


}

void TIEBomber::interact(std::shared_ptr<SpaceObject> other) {
    // empty implementation
}

std::string TIEBomber::createMissile(Position targetPos) {
    std::string missileName = "m_" + std::to_string(missilesCounter) + "_" + id;
    auto missile = std::make_unique<Missile>(position, targetPos, missileName);
    bomberMissiles.push_back(missileName);
    missilesMap[missileName] = std::move(missile);
    return missileName;

}


void TIEBomber::shoot(Position targetPos) {
    missilesCounter++;
    std::string missileName = createMissile(targetPos);
    std::cout << "TIE Bomber " << id << " shoot missile " << missileName << " to " << targetPos << std::endl;

}


int TIEBomber::getMissilesCounter() const {
    return missilesCounter;
}

std::string TIEBomber::missileUpdate(const std::vector<std::pair<std::string, Position>>& falconsPositions){
    std::string falconName;
    for (const auto& missileName: bomberMissiles) {
        auto missile = std::dynamic_pointer_cast<Missile>(missilesMap[missileName]);
        falconName = missile->update(falconsPositions); // if missile hit falcon return falcon name
        if (missile->isMissileDestroyed()) {
            std::cout << "Missile " << getId() << " hits Falcon " << falconName << "at " << target << std::endl;
            // remove missile from the map
            // remove missile from the vector
            // kill falcon

        }
    }
    return falconName;
}