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



    else { // spaceship is stopped or docked
        updateMissionTime();
        destination = newDestination;
        direction = Direction(this->position, newDestination);
        state = SpaceshipState::MOVING;


    }


}

Position Spaceship::getCurrentPosition() {
    if (state == SpaceshipState::STOPPED) {
        return position; // If stopped, return the current position
    }

    // Calculate the angle to the destination
    float angleToDestination = Direction::calculateAngle(position, destination);
    direction = Direction(position, destination);


    // Calculate distance traveled in one hour (step size)
    float deltaX = (speed * std::cos(angleToDestination)) / 1000.0f; // Convert to kilometers
    float deltaY = speed * std::sin(angleToDestination) / 1000.0f; // Convert to kilometers
    Position newPosition(position.getX() + deltaX, position.getY() + deltaY);



    // Check if movement is in the right direction
    float currentDistance = position.distance(destination);
    float newDistance = newPosition.distance(destination);



    if (newDistance > currentDistance) {
        // Overshot the target: snap to the destination
        position = destination;
        setState(SpaceshipState::DOCKED); // Set state to DOCKED
        return destination;
    }

    // Check if the spaceship has reached or is very close to the destination
    if (newDistance < 0.1f) { // Threshold for reaching the destination
        position = destination; // Snap to destination
        setState(SpaceshipState::DOCKED); // Set state to DOCKED
        return destination;
    }

    position = newPosition; // Update position for further movement
    std::cout << position.getX() << " " << position.getY() << std::endl;

    float angle = Direction::calculateAngle(position, destination);

    if (std::abs(angleToDestination - angle) > 0.00001) {
        position = destination;
        setState(SpaceshipState::DOCKED); // Set state to DOCKED
        return destination;
    }

    return position;
}







void Spaceship::update() {
    position = getCurrentPosition();

}

void Spaceship::updateMissionTime() {
    this->startMissionTime = this->currentTime;
}

void Spaceship::stop() {
    this->state = SpaceshipState::STOPPED;
    position = getCurrentPosition();

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



Position Spaceship::getDestinationPosition() {
    return destination;
}

void Spaceship::clear() {

}
