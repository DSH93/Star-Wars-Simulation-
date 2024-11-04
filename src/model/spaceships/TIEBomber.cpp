//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/TIEBomber.h"





void TIEBomber::update() {
    // empty implementation


}

void TIEBomber::status() {
    std::cout << "TIE Bomber " << id << " at " << position << " ";

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

void TIEBomber::interact(std::shared_ptr<SpaceObject> other) {
    // empty implementation
}
