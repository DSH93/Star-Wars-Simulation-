//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_MILLENNIUMFALCON_H
#define STARWARSSIMULATION_MILLENNIUMFALCON_H


#include <memory>
#include <vector>
#include "Spaceship.h"

class MillenniumFalcon : public Spaceship {
private:
    int attPowerUnits = 5;
    int maxAttPowerUnits = 20;

public:
    MillenniumFalcon(Position& pos, std::string identifier, float speed = 3000.0f)
    : Spaceship(pos, std::move(identifier)) {
        this->setSpeed(speed);
    }

    void interact(std::shared_ptr<SpaceObject> other) override;
    void addMission();
    void update() override;
    void status() override;
    void fireMissile();
    void startMission();
    void finishMission();
    void loadAttPowerUnits();
    void killFalcon();
    std::vector<std::shared_ptr<SpaceObject>> getShuttlesInRadius();
    std::vector<std::shared_ptr<SpaceObject>> getBomberInRadius();
    int getAttPowerUnits() const;
    void setAttPowerUnits(int attPowerUnits);


};


#endif //STARWARSSIMULATION_MILLENNIUMFALCON_H
