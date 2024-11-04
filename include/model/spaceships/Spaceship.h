//
// Created by Dor Shukrun on 24/08/2024.
//

#ifndef STARWARSSIMULATION_SPACESHIP_H
#define STARWARSSIMULATION_SPACESHIP_H


#include <map>
#include "model/SpaceObject.h"

class Spaceship: public SpaceObject {
public:
    enum class SpaceshipState {
        STOPPED,
        DOCKED,
        MOVING,
        DEAD
    };
protected:
    SpaceshipState state;
    std::map<SpaceshipState, std::string> stateToString = {
            {SpaceshipState::STOPPED, "Stopped"},
            {SpaceshipState::DOCKED, "Docked"},
            {SpaceshipState::MOVING, "Moving"},
            {SpaceshipState::DEAD, "Dead"}
    };
    Position destination;
    Direction direction;
    float speed;
    int currentTime = 0;
    int startMissionTime = 0;




public:
    Spaceship(Position& pos, const std::string& identifier)
            : SpaceObject(pos, identifier),
              state(SpaceshipState::DOCKED),
              destination(pos),
              direction(Direction(pos, pos)),
              speed(500) // the default speed for spaceships is 500 km/h
              {}


    SpaceshipState getState() const {
        return state;
    }

    void setSpeed(float newSpeed) {
        this->speed = newSpeed;
    }

    void setState(SpaceshipState newState);

    const Position &getDestination() const;

    void setDestination(const Position &dest);

    const Direction &getDirection() const;

    void setDirection(const Direction &dir);

    Position getCurrentPosition() override; // Returns the current position of the spaceship based on the speed direction and time

    void updateMissionTime();

    virtual void move(const Position& newPosition);
    virtual void stop();
    virtual void update() override = 0;
    virtual void status() override = 0;
    virtual ~Spaceship() override = default;




};


#endif //STARWARSSIMULATION_SPACESHIP_H
