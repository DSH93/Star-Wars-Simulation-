//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_FORTRESSSTAR_H
#define STARWARSSIMULATION_FORTRESSSTAR_H

#include <vector>
#include <memory>
#include <iostream>
#include "SpaceObject.h"

class FortressStar : public SpaceObject {
private:
    int crystalAmount = 0;
    std::vector<std::shared_ptr<SpaceObject>> dockingShuttles;

public:
    FortressStar(int crystalAmount, Position position, std::string identifier)
            : SpaceObject(position, identifier), crystalAmount(crystalAmount) {}

    int getCrystalAmount() const {
        return crystalAmount;
    }

    void setCrystalAmount(int crystalAmount) {
        FortressStar::crystalAmount = crystalAmount;
    }

    void status() override {
        std::cout << "Fortress " << id << ", at Position: (" << position.getX() << ", " << position.getY()
                  << "), Inventory: " << crystalAmount << std::endl;
    }

    void interact(std::shared_ptr<SpaceObject> other) override {
        // Implementation for interaction with another SpaceObject
    }

    Position getCurrentPosition() override {
        return position; // Returns the current position of the fortress
    }

    void update() override {
        // Implementation for updating the state of the fortress
    }

    void addCrystals(int amount) {
        crystalAmount += amount;
    }

};

#endif //STARWARSSIMULATION_FORTRESSSTAR_H
