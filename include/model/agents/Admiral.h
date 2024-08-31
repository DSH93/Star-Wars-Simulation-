//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_ADMIRAL_H
#define STARWARSSIMULATION_ADMIRAL_H


// Admiral.h
#include <iostream>
#include "ImperialAgent.h"

class Admiral : public ImperialAgent {
public:
    Admiral (std::string name) : ImperialAgent(name) {}
    void displayRank() const override {
        std::cout << "Rank: Admiral" << std::endl;
    }
};


#endif //STARWARSSIMULATION_ADMIRAL_H
