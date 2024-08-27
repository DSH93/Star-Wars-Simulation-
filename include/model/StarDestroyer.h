//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_STARDESTROYER_H
#define STARWARSSIMULATION_STARDESTROYER_H


#include "Spaceship.h"

class StarDestroyer : public Spaceship{
private:


public:
    StarDestroyer(Position& pos, std::string identifier, float speed = 2000.0f)
    : Spaceship(pos, std::move(identifier)) {
        this->setSpeed(speed); // Set the speed of the spaceship
    }

};


#endif //STARWARSSIMULATION_STARDESTROYER_H
