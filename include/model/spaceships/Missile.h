//
// Created by Dor Shukrun on 07/11/2024.
//

#ifndef STARWARSSIMULATION_MISSILE_H
#define STARWARSSIMULATION_MISSILE_H


#include "model/SpaceObject.h"
#include <vector>


class Missile : public SpaceObject {
private:
    int startMissionTime;
    Position target;
    Direction direction;
    int distance;
    int speed;
    bool isDestroyed = false;


public:

    Missile(const Position &bomberPos, const Position &targetPos, const std::string &identifier);

    void status() override;

    void interact(std::shared_ptr<SpaceObject> other) override;

    Position getCurrentPosition() override;

    ~Missile() override = default;

    void update() override;

    void setTarget(const Position &misTarget);

    bool isMissileDestroyed() const;

    void destroy();

    std::string getId() const;

    std::string update(const std::vector<std::pair<std::string, Position>>& falconsPositions);

    Position getTarget() const;
};


#endif //STARWARSSIMULATION_MISSILE_H
