//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_STARDESTROYER_H
#define STARWARSSIMULATION_STARDESTROYER_H


#include <memory>
#include "Spaceship.h"
#include "model/agents/Admiral.h"

class StarDestroyer : public Spaceship{
private:
    int falconCounter = 0;
    std::shared_ptr<Admiral> pilot;

public:
    StarDestroyer(Position& pos, std::string identifier, float speed = 2000.0f, std::shared_ptr<Admiral> pilot = nullptr)
            : Spaceship(pos, std::move(identifier)), pilot(std::move(pilot)) {
        if (!pilot) {
            throw std::invalid_argument("Pilot cannot be null");
        }
    }

    void interact(std::shared_ptr<SpaceObject> other) override;
    void addMission();
    void update() override;
    void status() override;
    void fireMissile();
    void startMission();
    void finishMission();





};


#endif //STARWARSSIMULATION_STARDESTROYER_H
