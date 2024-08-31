//
// Created by Dor Shukrun on 24/08/2024.
//

#ifndef STARWARSSIMULATION_SHUTTLE_H
#define STARWARSSIMULATION_SHUTTLE_H

#include <memory>
#include <queue>
#include "Spaceship.h"
#include "model/agents/Midshipman.h"

class Shuttle : public Spaceship {
private:
    int crystalsContainers = 0;
    int maxCrystalsContainers = 5;
    int powerUnits = 10;
    int maxPowerUnits = 20;
    Position destination;
    std::queue<std::pair<Position, Position>> supplyMissions; // pair of source and destination for each mission <Space Station, Fortress Star>
    std::shared_ptr<Midshipman> pilot; // Midshipman that pilots the shuttle



public:
    Shuttle(Position &pos1, std::string identifier1, std::shared_ptr<Midshipman> pilot = nullptr)
            : Spaceship(pos1, std::move(identifier1)),
              destination(pos1), pilot(std::move(pilot)) {
        if (pilot == nullptr) {
            throw std::invalid_argument("Pilot cannot be null");
        }
    }

    void update() override;

    void status() override;

    void interact(std::shared_ptr<SpaceObject> other) override;

    void loadCrystals(int amount);

    void unloadCrystals(int amount);

    void loadPowerUnits();

    void unloadPowerUnits();

    void startSupplyMission();

    void addSupplyMission(std::pair<Position, Position> mission);

    void finishSupplyMission();


};


#endif //STARWARSSIMULATION_SHUTTLE_H
