//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_TIEBOMBER_H
#define STARWARSSIMULATION_TIEBOMBER_H

#include "Spaceship.h"
#include <vector>

class TIEBomber : public Spaceship {
private:
    std::vector<std::pair<Position, bool>> visitedPositions;

public:
    TIEBomber(Position& pos, std::string identifier, float speed = 1000.0f)
            : Spaceship(pos, std::move(identifier)), visitedPositions() {
        this->setSpeed(speed); // Set the speed of the spaceship
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

