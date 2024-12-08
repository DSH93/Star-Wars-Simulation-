//
// Created by Dor Shukrun on 07/11/2024.
//

#ifndef STARWARSSIMULATION_MISSILE_H
#define STARWARSSIMULATION_MISSILE_H


#include "model/SpaceObject.h"
#include "model/spaceships/Spaceship.h"
#include <vector>


class Missile : public Spaceship {
private:
    Position target;
    float distance;
    bool isDestroyed = false;


public:

    Missile(const Position &destroyer, const Position &targetPos, const std::string &identifier);


    void status() override;

    void interact(std::shared_ptr<SpaceObject> other) override;

    ~Missile() override = default;

    void update() override;

    void setTarget(const Position &misTarget);

    [[nodiscard]] bool isMissileDestroyed() const;

    std::string update(const std::vector<std::pair<std::string, Position>>& falconsPositions);

    [[nodiscard]] Position getTarget() const;
};


#endif //STARWARSSIMULATION_MISSILE_H
