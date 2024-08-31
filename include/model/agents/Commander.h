//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_COMMANDER_H
#define STARWARSSIMULATION_COMMANDER_H


// Commander.h
#include <iostream>
#include "ImperialAgent.h"

class Commander : public ImperialAgent {
public:
    Commander (std::string name) : ImperialAgent(name) {}
    void displayRank() const override {
        std::cout << "Rank: Commander" << std::endl;
    }
};


#endif //STARWARSSIMULATION_COMMANDER_H
