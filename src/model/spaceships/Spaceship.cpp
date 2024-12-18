//
// Created by Dor Shukrun on 24/08/2024.
//

#include <cmath>
#include <iomanip>

#include "model/spaceships/Spaceship.h"
#include "model/Timer.h"

Spaceship::Spaceship(const Position &pos, const std::string &identifier,
                     const std::vector<std::shared_ptr<SpaceObject>> &sites)
        : SpaceObject(pos, identifier),
          state(SpaceshipState::STOPPED),
          method(flightMethod::DESTINATION),
          destination(pos),
          direction(Direction(pos, pos)),
          speed(SPACESHIP_DEFAULT_SPEED),
          sites(sites) {

    for (const auto &site: sites) {
        sitesMap[site->getPosition()] = site; // find the site by its positionCMD
        sitesDestinations[site->getId()] = site->getPosition(); // find the site by its id
    }
}


void Spaceship::setState(Spaceship::SpaceshipState newState) {
    this->state = newState;
}

Spaceship::SpaceshipState Spaceship::getState(){
    return state;
}

void Spaceship::setCourse(float angle) {
    method = flightMethod::COURSE;
    Logger::getInstance().log("Spaceship " + id + " set courseCMD to " + std::to_string(angle) + " degrees");
    auto dir = Direction(angle);
    this->direction = dir;
    state = SpaceshipState::MOVING;

}

void Spaceship::setSiteDestination(const std::string &siteName){
    if (getType() == "Falcon") {
        Logger::getInstance().log("Falcon cannot set destinationCMD by site");
        return;
    }
    method = flightMethod::DESTINATION;
    move(sitesDestinations[siteName]);
}


void Spaceship::setDestinationByPosition(const Position &dest) {
    method = flightMethod::POS;
    move(dest);
}

void Spaceship::move(const Position &newDestination) {
    if (this->state == SpaceshipState::DEAD) {
        Logger::getInstance().log("Spaceship is dead");
        return;
    } else { // spaceship is stopped or docked
        destination = newDestination;
        direction = Direction(this->position, newDestination);
        state = SpaceshipState::MOVING;

    }
}

void Spaceship::logCreation(const std::string &spaceshipType, const std::string &identifier, float velocity) {
    Logger::getInstance().log(spaceshipType + " created with ID: " + identifier + " and speed: " + std::to_string(velocity) + " km/h");
}

Position Spaceship::calculateCoursePosition() {
    float deltaX = (speed * std::cos(direction.getAngleInRadians())) / UNIT_TO_KM_CONVERSION;
    float deltaY = speed * std::sin(direction.getAngleInRadians()) / UNIT_TO_KM_CONVERSION;
    position = Position(position.getX() - deltaX, position.getY() + deltaY);
    return position;
}

Position Spaceship::calculateNewPosition() {
    float angleToDestination = Direction::calculateAngle(position, destination);
    direction = Direction(position, destination);

    // Calculate distance traveled in one hour (step size)
    float deltaX = (speed * std::cos(angleToDestination)) / UNIT_TO_KM_CONVERSION;
    float deltaY = speed * std::sin(angleToDestination) / UNIT_TO_KM_CONVERSION;
    Position newPosition(position.getX() + deltaX, position.getY() + deltaY);

    // Check if movement is in the right direction
    float currentDistance = Position::distance(position, destination);
    float newDistance = Position::distance(newPosition, destination);

    this->position = newPosition;
    float angle = Direction::calculateAngle(position, destination);

    // Check if spaceship needs to dock
    if (newDistance > currentDistance ||
        newDistance < SPACESHIP_MIN_DISTANCE_THRESHOLD ||
        std::abs(angleToDestination - angle) > SPACESHIP_ANGLE_THRESHOLD) {
        position = destination;
        if (method == flightMethod::POS) setState(SpaceshipState::STOPPED);
        if(sitesMap.find(destination) != sitesMap.end()) setState(SpaceshipState::DOCKED);


        return destination;
    }

    return position;
}

Position Spaceship::getCurrentPosition() {
    if (state == SpaceshipState::STOPPED || state == SpaceshipState::DEAD) return position; // If stopped, return the current positionCMD
    if (method == flightMethod::COURSE) return calculateCoursePosition();
    return calculateNewPosition();
}

void Spaceship::update() {
    position = getCurrentPosition();
}

void Spaceship::stop() {
    this->state = SpaceshipState::STOPPED;
    position = getCurrentPosition();

}

void Spaceship::printState(const std::string& typeName) {
    switch (state) {
        case SpaceshipState::STOPPED:
            Logger::getInstance().log(typeName + " " + id + " at " + position.toString() + " Stopped");
            std::cout << typeName << " " << id << " at " << position.toString() << " Stopped\n";
            break;

        case SpaceshipState::DOCKED:
            Logger::getInstance().log(typeName + " " + id + " at " + position.toString() + " Docked");
            std::cout << typeName << " " << id << " at " << position.toString() << " Docked\n";
            break;

        case SpaceshipState::DEAD:
            Logger::getInstance().log(typeName + " " + id + " at " + position.toString() + " Destroyed");
            std::cout << typeName << " " << id << " at " << position.toString() << " Destroyed\n";
            break;

        case SpaceshipState::MOVING:
            printFlightMethod(typeName); // Delegate to flight method printing
            break;

        default:
            std::cerr << "Unknown spaceship state" << std::endl;
            break;
    }
}

void Spaceship::printFlightMethod(const std::string& typeName) {
    std::string msg;
    std::ostringstream formattedSpeed;
    std::ostringstream formattedDegree;

    formattedSpeed << std::fixed << std::setprecision(2) << speed;


    switch (method) {
        case flightMethod::DESTINATION:
            msg = typeName + " " + id + " at " + position.toString() + " Heading to " +
                  sitesMap[destination]->getId() + ", speed " + formattedSpeed.str() + " km/h\n";
            break;

        case flightMethod::COURSE:
            formattedDegree << std::fixed << std::setprecision(2) << direction.getAngle();
            msg = typeName + " " + id +" at " + position.toString() + " Heading on courseCMD " + formattedDegree.str() + " deg, speed " + formattedSpeed.str() + " km/h\n";
            break;

        case flightMethod::POS:
            msg = typeName + " " + id + " at " + position.toString() + " Heading to " +
                  destination.toString() + ", speed " + formattedSpeed.str() + " km/h\n";
            break;

        default:
            std::cerr << "Unknown flight method" << std::endl;
            return;
    }
    Logger::getInstance().log(msg);
    std::cout << msg;
}

void Spaceship::status() {
    std::string type = getType();
    printState(type);
}

std::string Spaceship::getType() const {
    return "Spaceship";
}

