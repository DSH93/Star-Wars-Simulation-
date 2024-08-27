//
// Created by Dor Shukrun on 24/08/2024.
//

#ifndef STARWARSSIMULATION_SPACESHIP_H
#define STARWARSSIMULATION_SPACESHIP_H


#include <map>
#include "SpaceObject.h"

class Spaceship: public SpaceObject {
public:
    enum class SpaceshipState {
        STOPPED,
        PARKED,
        MOVING,
        FINISHED
    };
private:
    SpaceshipState state;
    std::map<SpaceshipState, std::string> stateToString = {
            {SpaceshipState::STOPPED, "Stopped"},
            {SpaceshipState::PARKED, "Parked"},
            {SpaceshipState::MOVING, "Moving"},
            {SpaceshipState::FINISHED, "Finished"}
    };
    Position destination;
    Direction direction;
    float speed;
    int currentTime = 0;
    int startMissionTime = 0;




public:
    Spaceship(Position& pos, std::string identifier)
            : SpaceObject(pos, std::move(identifier)),
              state(SpaceshipState::PARKED),
              destination(pos),
              direction(Direction(pos, pos)),
              speed(500) // the default speed for spaceships is 500 km/h
              {}


    SpaceshipState getState() const {
        return state;
    }

    void setSpeed(float speed) {
        this->speed = speed;
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
    virtual void update() = 0;
    virtual void status() = 0;



};


#endif //STARWARSSIMULATION_SPACESHIP_H
