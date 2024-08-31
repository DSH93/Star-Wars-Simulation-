//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_MIDSHIPMAN_H
#define STARWARSSIMULATION_MIDSHIPMAN_H

#include <iostream>
#include "ImperialAgent.h"

class Midshipman : public ImperialAgent {
public:
    Midshipman (std::string name) : ImperialAgent(name) {}
    void displayRank() const override {
        std::cout << "Rank: Midshipman" << std::endl;
    }
};



#endif //STARWARSSIMULATION_MIDSHIPMAN_H
