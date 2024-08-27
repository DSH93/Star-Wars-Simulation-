//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_FORTRESSSTAR_H
#define STARWARSSIMULATION_FORTRESSSTAR_H

#include <vector>
#include <memory>
#include "SpaceObject.h"

class FortressStar : public SpaceObject {
private:
    int crystalAmount = 0;
    std::vector<std::shared_ptr<SpaceObject>> dockingShuttles;
public:
    FortressStar(int crystalAmount, Position position, std::string identifier): SpaceObject(position, identifier) {}

    int getCrystalAmount() const;

    void setCrystalAmount(int crystalAmount);

    void status() override;

    void interact(std::shared_ptr<SpaceObject> other) override;

    void update();

};

#endif //STARWARSSIMULATION_FORTRESSSTAR_H
