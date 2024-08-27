//
// Created by Dor Shukrun on 24/08/2024.
//

#include "model/Spaceship.h"
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
    this->destination = newDestination;
    this->direction = Direction(this->position, newDestination);
    this->state = SpaceshipState::MOVING;
    this->updateMissionTime();
}

Position Spaceship::getCurrentPosition() {
    float AC = this->speed * (this->currentTime - this->startMissionTime);
    float angle = this->direction.getAngle();
    float x = this->position.getX() + AC * cos(angle);
    float y = this->position.getY() + AC * sin(angle);
    return Position(x, y);

}

void Spaceship::update() {
    int currentTick = Timer::getCurrentTick();
    this->currentTime = currentTick;
}

void Spaceship::updateMissionTime() {
    this->startMissionTime = this->currentTime;
}

void Spaceship::stop() {
    this->state = SpaceshipState::STOPPED;
    //TODO update the mission time and current position
}
