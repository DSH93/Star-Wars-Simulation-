//
// Created by Dor Shukrun on 07/11/2024.
//

#include "model/spaceships/Missile.h"



Missile::Missile(const Position &bomberPos, const Position &targetPos, const std::string &identifier)
        : SpaceObject(bomberPos, identifier), direction(bomberPos, targetPos), target(targetPos), speed(3000.0f) {
    startMissionTime = Timer::getCurrentTick();
    distance = bomberPos.distance(targetPos);
}



void Missile::setTarget(const Position &target) { // change the target of the missile
    this->target = target;
    direction = Direction(getCurrentPosition(), target);

}

bool Missile::isMissileDestroyed() const {
    return isDestroyed;
}

void Missile::destroy() {
    if (getCurrentPosition() == target) {
        isDestroyed = true;
    }
}


void Missile::status() {
    std::string id = getId();
    std::cout << "Missile " << id << "current position: " << getCurrentPosition() <<"Target" << target << std::endl;


}

void Missile::interact(std::shared_ptr<SpaceObject> other) {

}

Position Missile::getCurrentPosition() {
    float time = Timer::getCurrentTick() - startMissionTime;
    float distanceCovered = time * speed;
    if (distanceCovered >= distance) {
        return target;
    }
    return direction.getCurrentPositionBySpeedAndTime(speed, time, position);


}

void Missile::update() {

}

std::string Missile::getId() const {
    return id;
}
