//
// Created by Dor Shukrun on 23/08/2024.
//

#ifndef STARWARSSIMULATION_SPACEOBJECT_H
#define STARWARSSIMULATION_SPACEOBJECT_H

#include "Position.h"
#include "Direction.h"
#include <string>
#include <utility>
#include <stdexcept> // For std::invalid_argument
#include <memory>

class SpaceObject {
protected:
    Position position;
    std::string id;
    int currentTime;

public:
    SpaceObject(Position& pos, const std::string& identifier)
            : position(pos), id(validateId(identifier)) {}

    Position getPosition() const { return position; }
    void setPosition(const Position& pos) { position = pos; }
    std::string getId() const { return id; }
    virtual void status() = 0;
    virtual void interact(std::shared_ptr<SpaceObject> other) = 0;
    virtual Position getCurrentPosition() = 0;
    virtual ~SpaceObject() = default;
    virtual void update() = 0;


private:
    static std::string validateId(const std::string& identifier) {
        if (identifier.length() > 15) { // 15 because indexing starts from 0
            throw std::invalid_argument("ID must be less than 16 characters.");
        }
        return identifier;
    }
};

#endif //STARWARSSIMULATION_SPACEOBJECT_H

