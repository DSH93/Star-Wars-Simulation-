//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/TIEBomber.h"

void TIEBomber::move(const Position &newPosition) {
    Spaceship::move(newPosition);
}

void TIEBomber::stop() {
    Spaceship::stop();
}

void TIEBomber::update() {
    // empty implementation


}

void TIEBomber::status() {
    // empty implementation

}

void TIEBomber::randomPatrol() {
    // empty implementation

}

void TIEBomber::addPatrolMission() {
    // empty implementation

}

void TIEBomber::finishPatrolMission() {
    // empty implementation

}

Position TIEBomber::findClosestSpaceSite() {
    return Position(0, 0);     // empty implementation

}

void TIEBomber::flyToClosestSpaceSite() {
    // empty implementation


}
