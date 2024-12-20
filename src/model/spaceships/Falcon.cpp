//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/Falcon.h"

Falcon::Falcon(Position& pos, const std::string& identifier, const std::vector<std::shared_ptr<SpaceObject>>& sites)
        : Spaceship(pos, identifier, sites) {
    this->setSpeed(FALCON_DEFAULT_SPEED);
    logCreation("Falcon", identifier, speed);
}


void Falcon::killFalcon() {
    std::cout << "Falcon " << id << " was destroyed" << std::endl;
    setState(SpaceshipState::DEAD);
}

int Falcon::getAttPowerUnits() const {
    return attPowerUnits;

}


void Falcon::increaseAttPowerUnits() {
    if (attPowerUnits == maxAttPowerUnits) {
        Logger::getInstance().log("Falcon " + id + " cannot increase attack power units. Maximum reached.");
        return;
    }
    attPowerUnits++;
}

void Falcon::decreaseAttPowerUnits() {
    attPowerUnits--;
}



bool Falcon::canAttack(int attackerPower, int targetDefense, const Position &targetPos, float distanceToTarget,
                       float closetBomber) {
    float velocity = Spaceship::getSpeed();
    if (distanceToTarget >= velocity + FALCON_MAX_DISTANCE_TO_TARGET) { // 100K in the next turn
        Logger::getInstance().log("Falcon " + id + " cannot attack target " + targetPos.toString() + ERROR_TARGET_TOO_FAR +" Distance: " + std::to_string(distanceToTarget));
        std::cout << ERROR_TARGET_TOO_FAR << std::endl;
        return false;
    }

    if (attackerPower <= targetDefense) {
        Logger::getInstance().log("Falcon " + id + " cannot attack target " + targetPos.toString() + ERROR_TARGET_TOO_STRONG);
        std::cout << ERROR_TARGET_TOO_STRONG << std::endl;
        return false;
    }

    if (closetBomber <= FALCON_MIN_DISTANCE_TO_BOMBER) { // 250Km
        Logger::getInstance().log("Falcon " + id + " cannot attack target " + targetPos.toString() + ERROR_BOMBER_TOO_CLOSE);
        std::cout << ERROR_BOMBER_TOO_CLOSE << std::endl;
        return false;
    }

    return true;
}

void Falcon::attack(const std::shared_ptr<Shuttle>& target, float distanceToTarget, float closetBomber) {
    Position targetPos = target->getCurrentPosition();
    if (target->getState() == SpaceshipState::DEAD || getState() == SpaceshipState::DEAD) return;
        if (canAttack(getAttPowerUnits(), target->getDefPowerUnits(), targetPos, distanceToTarget, closetBomber)) { // attack succeeded
            interact(target); // Move interaction logic here
            Logger::getInstance().log("Falcon " + id + " attacked target " + target->getId());
        } else { // attack failed
            decreaseAttPowerUnits();
            setState(SpaceshipState::STOPPED);
            if (getAttPowerUnits() == 0) setState(SpaceshipState::DEAD);
        }
    target->decreaseDefPowerUnits();
    if (target->getDefPowerUnits() == 0) {
        target->setState(SpaceshipState::DEAD);
        std::cout << "Shuttle destroyed!" << std::endl;
        Logger::getInstance().log("Shuttle " + target->getId() + " was destroyed");
    }


}

void Falcon::interact(std::shared_ptr<SpaceObject> other) {
    auto shuttleTarget = std::dynamic_pointer_cast<Shuttle>(other);
    if (shuttleTarget) {
        Logger::getInstance().log("Falcon " + id + " is attacking Shuttle " + shuttleTarget->getId() + "attacker power: " + std::to_string(getAttPowerUnits()) + " target defense: " + std::to_string(shuttleTarget->getDefPowerUnits()));
        std::cout << "Falcon attacking Shuttle: " << shuttleTarget->getId() << std::endl;

        increaseAttPowerUnits();
        shuttleTarget->setState(SpaceshipState::STOPPED);
        shuttleTarget->unloadCrystals();
        setState(SpaceshipState::STOPPED);

    } else {
        std::cerr << "Falcon cannot interact with this object." << std::endl;
        Logger::getInstance().log("Falcon " + id + " cannot interact with object " + other->getId());
    }
}


