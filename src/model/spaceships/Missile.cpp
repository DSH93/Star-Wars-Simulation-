//
// Created by Dor Shukrun on 07/11/2024.
//

#include <vector>
#include "model/spaceships/Missile.h"



Missile::Missile(const Position &destroyer, const Position &targetPos, const std::string &identifier, const std::vector<std::shared_ptr<SpaceObject>>& sites)
        : Spaceship(const_cast<Position&>(destroyer), identifier, sites),
          target(targetPos) {
    this->destination = targetPos;
    setSpeed(MISSILE_SPEED);
    distance = Position::distance(destroyer,targetPos);
    setState(SpaceshipState::MOVING);
    Timer::getCurrentTick();
    direction = Direction(destroyer, targetPos);
    Logger::getInstance().log("Missile " + id + " created at " + position.toString() + " Heading to Target: " + target.toString());
}


bool Missile::isMissileDestroyed() const {
    return isDestroyed;
}


void Missile::status() {
    if (isDestroyed) {
        std::cout << "Missile  " << id << " at " << position.toString() << " Destroyed\n";
        Logger::getInstance().log("Missile  " + id + " at " + position.toString() + " Destroyed");
        return;
    }
    Logger::getInstance().log("Missile " + id + " at " + position.toString() + " Heading to Target: " + target.toString());
    std::cout << "Missile " << id << " "<< position <<", Heading to Target: " << target.toString() << std::endl;
}


Position Missile::getTarget() const {
    return target;
}

std::string Missile::updateAndCheckTarget(const std::vector<std::pair<std::string, Position>>& falconsPositions) {
    Spaceship::update();
    Logger::getInstance().log("Missile " + id + " at " + position.toString() + " Heading to Target: " + target.toString());
    std::string falconName;
    for (auto &falcon: falconsPositions) {
        if (falcon.second == target && position == target) {
            falconName = falcon.first;
            Logger::getInstance().log("Missile " + id + " at " + position.toString() + " Destroyed Falcon " + falconName);
            isDestroyed = true;
            break;
        }

    }

    return falconName;

}



