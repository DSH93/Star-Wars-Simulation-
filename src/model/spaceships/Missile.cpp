//
// Created by Dor Shukrun on 07/11/2024.
//

#include <vector>
#include "model/spaceships/Missile.h"



Missile::Missile(const Position &bomberPos, const Position &targetPos, const std::string &identifier)
        : SpaceObject(bomberPos, identifier), direction(bomberPos, targetPos), target(targetPos), speed(3000.0f) {
    startMissionTime = Timer::getCurrentTick();
    distance = bomberPos.distance(targetPos);
}



void Missile::setTarget(const Position &misTarget) { // change the misTarget of the missile
    this->target = misTarget;
    direction = Direction(getCurrentPosition(), misTarget);


}

bool Missile::isMissileDestroyed() const {
    return isDestroyed;
}

void Missile::destroy() {
    if (getCurrentPosition() == target) {

    }
}


void Missile::status() {
    std::string id = getId();
    std::cout << "Missile " << id << "current position: " << getCurrentPosition() <<"Target" << target << std::endl;


}

void Missile::interact(std::shared_ptr<SpaceObject> other) {

}

Position Missile::getCurrentPosition() {
    int time = Timer::getCurrentTick() + 1 - startMissionTime;
    int distanceCovered = time * speed;
    if (distanceCovered >= distance) {
        return target;
    }
    return direction.getCurrentPositionBySpeedAndTime(speed, time, position);


}

std::string Missile::update(const std::vector<std::pair<std::string, Position>>& falconsPositions) {
    std::string falconName;
    for (auto &falcon: falconsPositions) {
        if (falcon.second == target && target == getCurrentPosition()) {
            falconName = falcon.first;
            isDestroyed = true;
            break;
        }

    }

    return falconName;

}

std::string Missile::getId() const {
    return id;
}

void Missile::update() {


}
