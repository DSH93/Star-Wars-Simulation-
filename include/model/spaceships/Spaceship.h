//
// Created by Dor Shukrun on 24/08/2024.
//

#ifndef STARWARSSIMULATION_SPACESHIP_H
#define STARWARSSIMULATION_SPACESHIP_H


#include <map>
#include "model/SpaceObject.h"
#include <queue>

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
    int startMissionTime = Timer::getCurrentTick();





public:
    Spaceship(Position& pos, const std::string& identifier)
            : SpaceObject(pos, identifier),
              state(SpaceshipState::STOPPED),
              destination(pos),
              direction(Direction(pos, pos)),
              speed(500) // the default speed for spaceships is 500 km/h
              {}


    void setSpeed(float newSpeed) {
        this->speed = newSpeed;
    }

    [[nodiscard]] float getSpeed() const {return speed;}
    void setState(SpaceshipState newState);

    [[nodiscard]] const Position &getDestination() const;

    void setDestination(const Position &dest);

    [[nodiscard]] const Direction &getDirection() const;

    void setDirection(const Direction &dir);

    Position getCurrentPosition() override; // Returns the current position of the spaceship based on the speed direction and time

    void updateMissionTime();


    virtual void clear()  = 0;
    virtual void move(const Position& newPosition);
    virtual void stop();
    void interact(std::shared_ptr<SpaceObject> other) override = 0; // pure virtual function
    void update() override = 0;
    void status() override = 0;

    ~Spaceship() override = default;
    Position getDestinationPosition();
};


#endif //STARWARSSIMULATION_SPACESHIP_H
