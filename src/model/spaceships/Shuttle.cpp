//
// Created by Dor Shukrun on 24/08/2024.
//

#include <sstream>
#include "model/spaceships/Shuttle.h"
#include "model/SpaceStation.h"

void Shuttle::status() {

    std::ostringstream status;
    status << "Shuttle: " << id << "\nPilot: "  << "Midshipman, " << pilot << "\nCrystals: " << crystalsContainers << "/"
           << maxCrystalsContainers
           << "\nPower units: " << powerUnits << "/" << maxPowerUnits <<"\nCurrent location: " << position << "Destination: " << destination;

    std::cout << status.str() << std::endl;

}

void Shuttle::loadCrystals(int amount) {
    this->crystalsContainers += amount;

}

void Shuttle::interact(std::shared_ptr<SpaceObject> other) {
    if (typeid(*other) == typeid(SpaceStation)) {
        // load crystals
    }
    if (typeid(*other) == typeid(Shuttle)) {
        // wave to other shuttle
    }
    // todo: add more interactions

}

void Shuttle::unloadCrystals(int amount) {

}

void Shuttle::loadPowerUnits() {

}

void Shuttle::unloadPowerUnits() {

}

void Shuttle::startSupplyMission() {
    destination = supplyMissions.front().second;
    this->setState(SpaceshipState::MOVING);
    this->move(destination);


}

void Shuttle::addSupplyMission(std::pair<Position, Position> mission) {
    supplyMissions.push(mission);
}

void Shuttle::finishSupplyMission() {
    supplyMissions.pop();
    if (!supplyMissions.empty()) startSupplyMission();
    else {
        position = destination;
        this->setState(SpaceshipState::FINISHED);
    }


}

