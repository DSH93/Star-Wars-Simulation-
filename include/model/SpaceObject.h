//
// Created by Dor Shukrun on 23/08/2024.
//

#ifndef STARWARSSIMULATION_SPACEOBJECT_H
#define STARWARSSIMULATION_SPACEOBJECT_H


#include "Position.h"
#include "Direction.h"
#include <string>
#include <utility>

class SpaceObject {
protected:
    Position position;
    std::string id;
    int currentTime;


public:
    SpaceObject(Position& pos, std::string  identifier)
            : position(pos), id(std::move(identifier)) {}

    Position getPosition() const { return position; }
    void setPosition(const Position& pos) { position = pos; }
    std::string getId() const { return id; }
    virtual void status() = 0;
    virtual void interact(std::shared_ptr<SpaceObject> other) = 0;
    virtual Position getCurrentPosition() = 0;
    virtual ~SpaceObject() = default;
};


#endif //STARWARSSIMULATION_SPACEOBJECT_H
