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

void Shuttle::loadCrystals(const std::shared_ptr<SpaceStation> &st) {
    int crystals = st->unloadCrystals();
    this->crystalsContainers = crystals;
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


void Shuttle::addSupplyMission(const std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>> &mission) {
    supplyMissions.push(mission);
    if (supplyMissions.size() == 1) startSupplyMission();


}

void Shuttle::startSupplyMission() {
    if (supplyMissions.empty()) return;
    finishedMission = false;
    spaceStation = supplyMissions.front().first;

    fortressStar = supplyMissions.front().second;
    std::cout << position << " -> " << spaceStation->getId() << " " << spaceStation->getCurrentPosition() << " -> "
              << fortressStar->getId() << " " << fortressStar->getCurrentPosition() << std::endl;

    station = spaceStation->getCurrentPosition();
    fortress = fortressStar->getCurrentPosition();

    Spaceship::move(station);


}

void Shuttle::finishSupplyMission() {
    supplyMissions.pop();
    finishedMission = true;
}

void Shuttle::interact(std::shared_ptr<SpaceObject> other) {
    needToWait = true;
    auto spaceSt = std::dynamic_pointer_cast<SpaceStation>(other);
    auto fort = std::dynamic_pointer_cast<FortressStar>(other);
    if (spaceSt) {
        loadCrystals(spaceSt);
        std::cout << "Shuttle " << id << " start to load Crystals" << std::endl;

    } else if (fort) {
        std::cout << "Shuttle " << id << " start to unload Crystals" << std::endl;
        fort->addCrystals(crystalsContainers);
        unloadCrystals();
        finishSupplyMission();
    }


}


void Shuttle::update() {
    if (needToWait) {
        needToWait = false;
        if (position == station) std::cout << "Shuttle " << id << " is loading Crystals" << std::endl;
        else if (position == fortress) std::cout << "Shuttle " << id << " is unloading Crystals" << std::endl;
        return;
    }
    if (position == station) std::cout << "Shuttle " << id << " is moving to " << fortressStar->getId() << std::endl; // before the location update
    Spaceship::update();

    if (finishedMission){
        startSupplyMission();
        return;
    }

    if (position == station) {
        std::cout << "Shuttle " << id << " has arrived at " << spaceStation->getId() << std::endl;
        interact(spaceStation);
        Spaceship::move(fortress);


    } else if (position == fortress && !finishedMission) {
        std::cout << "Shuttle " << id << " has arrived at " << fortressStar->getId() << std::endl;
        interact(fortressStar);
    }
}

void Shuttle::clear() {

}

