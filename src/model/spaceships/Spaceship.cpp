//
// Created by Dor Shukrun on 24/08/2024.
//

#include <cmath>

#include "model/spaceships/Spaceship.h"
#include "model/Timer.h"

void Spaceship::setState(Spaceship::SpaceshipState newState) {
    this->state = newState;

}

const Position &Spaceship::getDestination() const {
    return this->destination;
}

void Spaceship::setDestination(const Position &dest) {
    this->destination = dest;

}

const Direction &Spaceship::getDirection() const {
    return this->direction;
}

void Spaceship::setDirection(const Direction &dir) {
    this->direction = dir;
}

void Spaceship::move(const Position &newDestination) {
    if (this->state == SpaceshipState::DEAD) {
        std::cerr << "Error: Spaceship is dead" << std::endl;
        return;
    }

    if (this->state == SpaceshipState::MOVING) {
        commands.push(newDestination);
    }

    else { // spaceship is stopped or docked
        updateMissionTime();
        destination = newDestination;
        direction = Direction(this->position, newDestination);
        state = SpaceshipState::MOVING;


    }


}

Position Spaceship::getCurrentPosition() {
    if (state == SpaceshipState::STOPPED) {
        return position;
    }
    currentTime = Timer::getCurrentTick();

    auto timeElapsed = float(currentTime - startMissionTime);
    float distanceTraveled = speed * timeElapsed;

    float angle = this->direction.getAngle();

    float deltaX = distanceTraveled * std::cos(angle) / 1000.0f;
    float deltaY = distanceTraveled * std::sin(angle) / 1000.0f;

    float newX = this->position.getX() + deltaX;
    float newY = this->position.getY() + deltaY;

    return {newX, newY};
}



void Spaceship::update() {
    currentTime = Timer::getCurrentTick();
    position = getCurrentPosition();
    if (position.distance(destination) == 0) {
        if (!commands.empty()) {
            destination = commands.front();
            commands.pop();
            direction = Direction(position, destination);
            updateMissionTime();
        } else {
            state = SpaceshipState::MOVING;
        }
    }

}

void Spaceship::updateMissionTime() {
    this->startMissionTime = this->currentTime;
}

void Spaceship::stop() {
    this->state = SpaceshipState::STOPPED;
    position = getCurrentPosition();
    this->clearCommands();

}

std::string getSpaceshipState(Spaceship::SpaceshipState state) {
    switch (state) {
        case Spaceship::SpaceshipState::STOPPED:
            return "Stopped";
        case Spaceship::SpaceshipState::DOCKED:
            return "Docked";
        case Spaceship::SpaceshipState::MOVING:
            return "Moving";
        case Spaceship::SpaceshipState::DEAD:
            return "Dead";
    }
    return "Unknown";
}


void Spaceship::clearCommands() {
    while (!commands.empty()) {
        commands.pop();
    }
}

Position Spaceship::getDestinationPosition() {
    return destination;
}
