//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/Falcon.h"



void Falcon::addMission() {
    // empty implementation


}

void Falcon::update() {
    position = Spaceship::getCurrentPosition();
}

void Falcon::status() {
    std::cout << "Falcon " << id
              << " at " << position
              << " | Status: " << stateToString[state]
              << std::endl;
}

void Falcon::startMission() {
    // empty implementation


}

void Falcon::finishMission() {
    // empty implementation


}

void Falcon::loadAttPowerUnits() {
    // empty implementation


}

void Falcon::killFalcon() {
    std::cout << "Falcon " << id << " was destroyed" << std::endl;
    setState(SpaceshipState::DEAD);
}

int Falcon::getAttPowerUnits() const {
    return attPowerUnits;

}

void setSpeed(int speed){
    speed = speed;
}

void Falcon::increaseAttPowerUnits() {
    attPowerUnits++;
}

void Falcon::decreaseAttPowerUnits() {
    attPowerUnits--;
}



bool Falcon::canAttack(int attackerPower, int targetDefense,const Position &attackerPos, const Position &targetPos, float distanceToTarget, float closetBomber) {
    float velocity = Spaceship::getSpeed();
    if (distanceToTarget >= velocity + 100.0) { // 100K in the next turn
        std::cout << distanceToTarget << std::endl;
        std::cerr << "Error: Target is too far for attack" << std::endl;
        return false;
    }

    if (attackerPower <= targetDefense) {
        std::cerr << "Error: Target has too much defense power" << std::endl;
        std::cout << "Falcon " << attackerPower << " vs " << targetDefense << " Shuttle" << std::endl;
        return false;
    }

    if (closetBomber <= 250) { // 250Km
        std::cerr << "Error: Falcon is too close to a bomber for attack" << std::endl;
        return false;
    }

    return true;
}

void Falcon::attack(const std::shared_ptr<Shuttle>& target, float distanceToTarget, float closetBomber) {
    Position attackerPos = getCurrentPosition();
    Position targetPos = target->getCurrentPosition();
        if (canAttack(getAttPowerUnits(), target->getDefPowerUnits(), attackerPos, targetPos, distanceToTarget, closetBomber)) { // attack succeeded
            interact(target); // Move interaction logic here
        } else { // attack failed
            decreaseAttPowerUnits();
            setState(Falcon::SpaceshipState::STOPPED);
            if (getAttPowerUnits() == 0) setState(Falcon::SpaceshipState::DEAD);
        }


}

void Falcon::interact(std::shared_ptr<SpaceObject> other) {
    auto shuttleTarget = std::dynamic_pointer_cast<Shuttle>(other);
    if (shuttleTarget) {
        std::cout << "Falcon attacking Shuttle: " << shuttleTarget->getId() << std::endl;
        shuttleTarget->decreaseDefPowerUnits();
        increaseAttPowerUnits();
        shuttleTarget->setState(Shuttle::SpaceshipState::STOPPED);
        shuttleTarget->unloadCrystals();
        setState(Falcon::SpaceshipState::STOPPED);
        if (shuttleTarget->getDefPowerUnits() == 0) {
            shuttleTarget->setState(Shuttle::SpaceshipState::DEAD);
            std::cout << "Shuttle destroyed!" << std::endl;
        }
    } else {
        std::cout << "Falcon cannot interact with this object." << std::endl;
    }
}


bool Falcon::isAlive() {
    return state != SpaceshipState::DEAD;
}

void Falcon::clear() {

}

