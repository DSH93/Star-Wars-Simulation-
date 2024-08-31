//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_TIEBOMBER_H
#define STARWARSSIMULATION_TIEBOMBER_H

#include "Spaceship.h"
#include "model/agents/Commander.h"
#include <vector>
#include <memory>

class TIEBomber : public Spaceship {
private:
    std::vector<std::pair<Position, bool>> visitedPositions;
    std::shared_ptr<Commander> pilot;

public:
    TIEBomber(Position& pos, std::string identifier, float speed = 1000.0f, std::shared_ptr<Commander> pilot = nullptr)
            : Spaceship(pos, std::move(identifier)), visitedPositions(), pilot(std::move(pilot)) {
        this->setSpeed(speed); // Set the speed of the spaceship
        if (pilot == nullptr) {
            throw std::invalid_argument("Pilot cannot be null");
        }
    }

    void move(const Position& newPosition) override;

    void stop() override;

    void update() override;

    void status() override;

    void randomPatrol();

    void addPatrolMission();

    void finishPatrolMission();

    Position findClosestSpaceSite();

    void flyToClosestSpaceSite();


};

#endif //STARWARSSIMULATION_TIEBOMBER_H

