//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/MillenniumFalcon.h"
#include "model/spaceships/Shuttle.h"

void MillenniumFalcon::interact(std::shared_ptr<SpaceObject> other) {
    // empty implementation


}

void MillenniumFalcon::addMission() {
    // empty implementation


}

void MillenniumFalcon::update() {
    // empty implementation


}

void MillenniumFalcon::status() {
    std::cout << "Millennium Falcon " << id << " at " << position << " ";


}

void MillenniumFalcon::fireMissile() {
    // empty implementation


}

void MillenniumFalcon::startMission() {
    // empty implementation


}

void MillenniumFalcon::finishMission() {
    // empty implementation


}

void MillenniumFalcon::loadAttPowerUnits() {
    // empty implementation


}

void MillenniumFalcon::killFalcon() {
    // empty implementation


}

std::vector<std::shared_ptr<SpaceObject>> MillenniumFalcon::getShuttlesInRadius() {
    return std::vector<std::shared_ptr<SpaceObject>>();     // empty implementation

}

std::vector<std::shared_ptr<SpaceObject>> MillenniumFalcon::getBomberInRadius() {
    return std::vector<std::shared_ptr<SpaceObject>>();     // empty implementation

}

int MillenniumFalcon::getAttPowerUnits() const {
    return attPowerUnits;

}

void MillenniumFalcon::setAttPowerUnits(int attPowerUnits) {
    // empty implementation


}

void MillenniumFalcon::increaseAttPowerUnits() {
    attPowerUnits++;
}

void MillenniumFalcon::decreaseAttPowerUnits() {
    attPowerUnits--;
}

bool MillenniumFalcon::canAttack(float attackerPower, float targetDefense,
                      const Position& attackerPos, const Position& targetPos, float distanceToTarget, float closetBomber) {


    if (distanceToTarget > 100000) { // 100Km
        std::cerr << "Error: Target is too far for attack" << std::endl;
        return false;
    }

    if (attackerPower <= targetDefense) {
        std::cerr << "Error: Target has too much defense power" << std::endl;
        return false;
    }

    if (closetBomber <= 250000) { // 250Km
        std::cerr << "Error: Falcon is too close to a bomber for attack" << std::endl;
        return false;
}

    return true;
}




void MillenniumFalcon::attack(std::shared_ptr<SpaceObject> target, float distanceToTarget, float closetBomber) {
    auto shuttleTarget = std::dynamic_pointer_cast<Shuttle>(target);
    Position attackerPos = getCurrentPosition();
    Position targetPos = target->getCurrentPosition();
    if (canAttack(getAttPowerUnits(), shuttleTarget->getDefPowerUnits(), attackerPos, targetPos, distanceToTarget, closetBomber)){ // attack succeeded

        shuttleTarget->decreaseDefPowerUnits();
        increaseAttPowerUnits();
        shuttleTarget->setState(Shuttle::SpaceshipState::STOPPED);
        int crystalsAmount = shuttleTarget->getCrystalsContainers();
        shuttleTarget->unloadCrystals(crystalsAmount);
        setState(MillenniumFalcon::SpaceshipState::STOPPED);
        if (shuttleTarget->getDefPowerUnits() == 0) shuttleTarget->setState(Shuttle::SpaceshipState::DEAD);



    } else { // attack failed
        decreaseAttPowerUnits();
        shuttleTarget->decreaseDefPowerUnits();
        setState(MillenniumFalcon::SpaceshipState::STOPPED);
        if (getAttPowerUnits() == 0) setState(MillenniumFalcon::SpaceshipState::DEAD);
        if (shuttleTarget->getDefPowerUnits() == 0) shuttleTarget->setState(Shuttle::SpaceshipState::DEAD);




}
}