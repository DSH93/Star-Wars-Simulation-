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
        Spaceship::move(mission.first->getPosition());
    } else {
        std::cerr << "Error: Shuttle is dead" << std::endl;
    }
}

void Shuttle::startSupplyMission() {
    if (supplyMissions.empty()) {
        return;
    }

    finishedMission = false;
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
    finishedMission = true;
    setState(SpaceshipState::DOCKED);

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
    if (state == SpaceshipState::MOVING) needToWait = true;
    if (destination == station || destination == fortress) {
        std::cout << "* Shuttle " << id << " is moving to " << destination.toString() << std::endl;
        Spaceship::move(destination);
    }
//    updatePositionAndState(); // todo maybe we can remove this line

}

void Shuttle::updatePositionAndState() {
    SpaceshipState oldState = state;
    getCurrentPosition();
    SpaceshipState newState = state;
    if (oldState == SpaceshipState::MOVING && newState == SpaceshipState::DOCKED) {
        needToWait = true;
    }
}

void Shuttle::update() {
    if (finishedMission){
        startSupplyMission();
        return;
    }

    if (supplyMissions.empty()) return;
    Spaceship::update();
    moveShuttle();
    updatePositionAndState();
}

void Shuttle::status() {
    std::cout << std::endl;
    std::string state = stateToString[this->state];
    if (this->state == SpaceshipState::DOCKED) {
        state += " at " + position.toString();
    }
    if (this->state == SpaceshipState::MOVING) {
        state += " to " + destination.toString();
    }

    std::cout << "Shuttle: " << id << " Position: " << position.toString()
              << " Waiting: " << needToWait
              //<< "\nPilot: " << "Midshipman, " << pilot->getName()
              //  << "\nCrystals: " << crystalsContainers << "/" << maxCrystalsContainers
              //    << "\nPower units: " << powerUnits << "/" << maxPowerUnits
              << "\nState: " << state << std::endl;
}
