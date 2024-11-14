//
// Created by Dor Shukrun on 24/08/2024.
//

#ifndef STARWARSSIMULATION_SHUTTLE_H
#define STARWARSSIMULATION_SHUTTLE_H

#include <memory>
#include <queue>
#include "Spaceship.h"
#include "model/agents/Midshipman.h"
#include "model/FortressStar.h"
#include "model/SpaceStation.h"

class Shuttle : public Spaceship {
private:
    int crystalsContainers = 0;
    int maxCrystalsContainers = 5;
    int powerUnits = 10;
    int maxPowerUnits = 20;
    int waiting = 0;
    Position fortress;
    Position station;
    std::shared_ptr<FortressStar> fortressStar;
    std::shared_ptr<SpaceStation> spaceStation;
    std::queue<std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>>> supplyMissions; // pair of source and fortress for each mission <Space Station, Fortress Star>
    std::shared_ptr<Midshipman> pilot; // Midshipman that pilots the shuttle
    bool needToWait = true;





public:
    Shuttle(Position &pos1, const std::string& identifier1, float speed, const std::shared_ptr<Midshipman>& pilot = nullptr)
            : Spaceship(pos1, identifier1),
              fortress(pos1), station(pos1), pilot(pilot) {

        this->setSpeed(speed);
        if (!pilot) {
            throw std::invalid_argument("Pilot cannot be null");
        }
        std::cout << "Shuttle created" << std::endl;
    }



    void update() override;

    void status() override;

    void interact(std::shared_ptr<SpaceObject> other) override;

    void loadCrystals(int amount);

    void unloadPowerUnits();

    void startSupplyMission();

    void finishSupplyMission();

    void decreaseDefPowerUnits();

    [[nodiscard]] int getDefPowerUnits() const;

    [[nodiscard]] int getCrystalsContainers() const;

    void moveShuttle();

    void waitThick();

    void unloadCrystals();

    void addSupplyMission(const std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>>& mission);


    void updatePositionAndState();
};


#endif //STARWARSSIMULATION_SHUTTLE_H
