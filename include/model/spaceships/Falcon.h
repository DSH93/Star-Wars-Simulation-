//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_FALCON_H
#define STARWARSSIMULATION_FALCON_H


#include <memory>
#include <vector>
#include "Spaceship.h"
#include "Shuttle.h"

class Falcon : public Spaceship {
private:
    int attPowerUnits = 5;
    int maxAttPowerUnits = 20;




public:
    Falcon(Position& pos, const std::string& identifier, float speed = 3000.0f)
    : Spaceship(pos, identifier) {
        this->setSpeed(speed);
        std::cout << "Millennium Falcon created" << std::endl;
    }

    void interact(std::shared_ptr<SpaceObject> other) override;
    void addMission();
    void update() override;
    void status() override;
    void startMission();
    void finishMission();
    void loadAttPowerUnits();
    void killFalcon();
    [[nodiscard]] int getAttPowerUnits() const;
    void increaseAttPowerUnits();
    void decreaseAttPowerUnits();
    bool isAlive();
    void clear() override;
    bool canAttack(int attackerPower, int targetDefense, const Position &attackerPos, const Position &targetPos,
                   float distanceToTarget, float closetBomber);

    void attack(const std::shared_ptr<Shuttle> &target, float distanceToTarget, float closetBomber);

};


#endif //STARWARSSIMULATION_FALCON_H
