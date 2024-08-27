//
// Created by Dor Shukrun on 24/08/2024.
//

#include <sstream>
#include "model/Shuttle.h"
#include "model/SpaceStation.h"

Shuttle::Shuttle(Position &pos1, std::string identifier1, std::string pilotName)
        : Spaceship(pos1, std::move(identifier1)),
          pilotName(std::move(pilotName)),
          destination(pos1) {}


void Shuttle::status() {
    std::ostringstream status;
    status << "Shuttle: " << id << "Pilot: " << pilotName << "Crystals: " << crystalsContainers << "/"
           << maxCrystalsContainers
           << "Power units: " << powerUnits << "/" << maxPowerUnits << "Destination: " << destination << "Position: "
           << position;
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

