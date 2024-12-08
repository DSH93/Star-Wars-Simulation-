//
// Created by Dor Shukrun on 07/11/2024.
//

#include <vector>
#include "model/spaceships/Missile.h"



Missile::Missile(const Position &destroyer, const Position &targetPos, const std::string &identifier): Spaceship(const_cast<Position&>(destroyer), identifier),target(targetPos) {
    setDestination(targetPos);
    setSpeed(3000.0f);
    distance = destroyer.distance(targetPos);
    setState(SpaceshipState::MOVING);
    startMissionTime = Timer::getCurrentTick();
    direction = Direction(destroyer, targetPos);
}

void Missile::setTarget(const Position &misTarget) { // change the misTarget of the missile
    this->target = misTarget;
    direction = Direction(getCurrentPosition(), misTarget);

}

bool Missile::isMissileDestroyed() const {
    return isDestroyed;
}

void Missile::status() {
    std::string id = getId();
    std::cout << "\n}=Missile==> " << id << " "<< position <<", Target: " << target.toString() << std::endl;

}

void Missile::interact(std::shared_ptr<SpaceObject> other) {

}

Position Missile::getTarget() const {
    return target;
}

std::string Missile::update(const std::vector<std::pair<std::string, Position>>& falconsPositions) {
    Spaceship::update();
    status();
    std::string falconName;
    for (auto &falcon: falconsPositions) {
        if (falcon.second == target && position == target) {
            falconName = falcon.first;
            isDestroyed = true;
            break;
        }

    }
    return falconName;
}

void Missile::update() {


}


