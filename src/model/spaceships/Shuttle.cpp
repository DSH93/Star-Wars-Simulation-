//
// Created by Dor Shukrun on 24/08/2024.
//

#include <sstream>
#include "model/spaceships/Shuttle.h"
#include "model/SpaceStation.h"
#include "model/FortressStar.h"


Shuttle::Shuttle(const Position &pos1, const std::string& identifier1, float speed, const std::shared_ptr<Midshipman>& pilot, const std::vector<std::shared_ptr<SpaceObject>>& sites)
        : Spaceship(pos1, identifier1, sites),
          fortress(pos1),
          station(pos1),
          pilot(pilot)
   {
    this->setSpeed(speed);
    if (!pilot) {
        throw std::invalid_argument("Pilot cannot be null");
    }

    logCreation("Shuttle", identifier1, speed);

}


int Shuttle::getDefPowerUnits() const {
    return powerUnits;
}

void Shuttle::loadCrystals(const std::shared_ptr<SpaceStation> &st) {
    int crystals = st->unloadCrystals();
    this->crystalsContainers = crystals;
}

void Shuttle::decreaseDefPowerUnits() {
    if (powerUnits == 0) return;
    powerUnits--;
    if (powerUnits == 0) {
        state = SpaceshipState::DEAD;
        return;
    }

}

void Shuttle::unloadCrystals() {
    crystalsContainers = 0;
}


void Shuttle::addSupplyMission(const std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>> &mission) {
    if (state == SpaceshipState::DEAD){
        Logger::getInstance().log("Shuttle " + id + " is dead and cannot receive a new supply mission");
        return;
    }
    Logger::getInstance().log("Shuttle " + id + " has received a new supply mission");
    supplyMissions.push(mission);
    if (supplyMissions.size() == 1) startSupplyMission();


}

void Shuttle::startSupplyMission() {
    method = flightMethod::DESTINATION;
    if (supplyMissions.empty()) return;
    finishedMission = false;
    spaceStation = supplyMissions.front().first;
    fortressStar = supplyMissions.front().second;
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
        spaceSt->interact(shared_from_this());
        std::cout << "Shuttle " << id << " start to load Crystals" << std::endl;

    } else if (fort) {
        std::cout << "Shuttle " << id << " start to unload Crystals" << std::endl;
        fort->addCrystals(crystalsContainers);
        fort->interact(shared_from_this());
        unloadCrystals();
        finishSupplyMission();
    }


}

void Shuttle::status() {
    Spaceship::status();
    std::cout << "Containers: " << crystalsContainers << "/" << maxCrystalsContainers << std::endl;
    std::cout << "Def: " << powerUnits <<"/"  << maxPowerUnits << std::endl;

}


void Shuttle::update() {

    if (needToWait) {
        needToWait = false;
        if (position == station) std::cout << "Shuttle " << id << " is loading Crystals" << std::endl;
        else if (position == fortress) std::cout << "Shuttle " << id << " is unloading Crystals" << std::endl;
        return;
    }
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

