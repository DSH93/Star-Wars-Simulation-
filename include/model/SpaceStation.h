//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_SPACESTATION_H
#define STARWARSSIMULATION_SPACESTATION_H


#include <vector>
#include <memory>
#include "SpaceObject.h"

class SpaceStation : public SpaceObject {
private:
    int crystalsAmount;
    int productionRate;
    std::vector<std::shared_ptr<SpaceObject>> dockingShuttles; // vector of docking shuttles avoiding circular dependency
public:
    SpaceStation(int crystalsAmount, int productionRate, Position position, std::string identifier);

    [[nodiscard]] int getCrystalsAmount() const;

    void status() override;

    void interact(std::shared_ptr<SpaceObject> other) override;

    void update() override;

    Position getCurrentPosition() override;

    int unloadCrystals();

    void toString() const;
};


#endif //STARWARSSIMULATION_SPACESTATION_H
