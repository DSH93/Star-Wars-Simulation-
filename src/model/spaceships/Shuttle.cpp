//
// Created by Dor Shukrun on 24/08/2024.
//

#include <sstream>
#include "model/spaceships/Shuttle.h"
#include "model/SpaceStation.h"
#include "model/FortressStar.h"


int Shuttle::getDefPowerUnits() const {
    return powerUnits;
}

int Shuttle::getCrystalsContainers() const {
    return crystalsContainers;
}

void Shuttle::decreaseDefPowerUnits() {
    powerUnits--;
}

void Shuttle::unloadCrystals() {
    crystalsContainers = 0;
}

void Shuttle::unloadPowerUnits() {
    powerUnits = 0;
}


void Shuttle::addSupplyMission(const std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>> &mission) {
    if (state != SpaceshipState::DEAD) {
        supplyMissions.push(mission);
    } else {
        std::cerr << "Error: Shuttle is dead" << std::endl;
    }
}

void Shuttle::startSupplyMission() {
    if (supplyMissions.empty()) {
        std::cerr << "Error: No supply missions" << std::endl;
        return;
    }

    if (state == SpaceshipState::STOPPED || (state == SpaceshipState::DOCKED && position == fortress)) {
        station = supplyMissions.front().first->getPosition(); // get the station position
        fortress = supplyMissions.front().second->getPosition(); // get the fortress position
        spaceStation = supplyMissions.front().first;
        fortressStar = supplyMissions.front().second;
        moveShuttle();
    } else {
        std::cout << "Shuttle is on a mission, the mission will start when the shuttle arrives to the fortress"
                  << std::endl;
    }
}

void Shuttle::finishSupplyMission() {
    supplyMissions.pop();
    setState(SpaceshipState::DOCKED);
    if (!supplyMissions.empty()) startSupplyMission();
}

void Shuttle::loadCrystals(int amount) {
    this->crystalsContainers += amount;
}

void Shuttle::interact(std::shared_ptr<SpaceObject> other) {

    if (other->getId() == spaceStation->getId()) {
        setState(SpaceshipState::DOCKED);
        crystalsContainers = spaceStation->unloadCrystals();
        std::cout << "* Shuttle loaded " << crystalsContainers << " crystals at " << spaceStation->getId() << std::endl;
    } else if (other->getId() == fortressStar->getId()) {
        setState(SpaceshipState::DOCKED);
        std::cout << "* Shuttle unloading " << crystalsContainers << " crystals to Fortress Star "
                  << fortressStar->getId() << std::endl;
        fortressStar->addCrystals(crystalsContainers);
        unloadCrystals();
        finishSupplyMission();
    } else {
        std::cerr << "Error: Invalid object" << std::endl;
    }
}

void Shuttle::moveShuttle() {
    if (position == station) destination = fortress;

    if (state == SpaceshipState::DOCKED && needToWait) {
        std::cout << "* Shuttle " << id << "has to wait for 1 time unit" << std::endl;
        needToWait = false;
        if (position == station) interact(spaceStation);
        if (position == fortress) interact(fortressStar);
        return;
    }
    if (state == SpaceshipState::STOPPED) destination = station;

    if (state == SpaceshipState::MOVING) {
        needToWait = true;


    }

    direction = Direction(position, destination);
    setState(SpaceshipState::MOVING);
    updatePositionAndState();



}


void Shuttle::updatePositionAndState() {
    float angle = Direction::calculateAngle(position, destination);
    position = getCurrentPosition();
    float angle2 = Direction::calculateAngle(position, destination);

    if (angle != angle2 && state == SpaceshipState::MOVING) {
        position = destination;
        std::cout << "Shuttle " << id << " has arrived at " << destination << std::endl;
        needToWait = true;
        setState(SpaceshipState::DOCKED);
    }
}


void Shuttle::update() {
    if (supplyMissions.empty()) {
        std::cerr << "Error: No supply missions" << std::endl;
        return;
    }
    if (state == SpaceshipState::DOCKED) {
        moveShuttle(); // move to fortress

    } else updatePositionAndState();
    status();

}


void Shuttle::status() {
    std::string state = stateToString[this->state];
    if (this->state == SpaceshipState::DOCKED) {
        state += " at " + position.toString();
    }
    if (this->state == SpaceshipState::MOVING) {
        state += "to " + destination.toString();
    }

    std::cout << "Shuttle: " << id
              << "\nPosition: " << position
              << "waiting: " << needToWait
              //<< "\nPilot: " << "Midshipman, " << pilot->getName()
              //  << "\nCrystals: " << crystalsContainers << "/" << maxCrystalsContainers
              //    << "\nPower units: " << powerUnits << "/" << maxPowerUnits
              << "\nState: " << state << std::endl;
}
