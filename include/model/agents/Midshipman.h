//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_MIDSHIPMAN_H
#define STARWARSSIMULATION_MIDSHIPMAN_H

#include <iostream>
#include "ImperialAgent.h"

class Midshipman : public ImperialAgent {
public:
    explicit Midshipman (const std::string& name) : ImperialAgent(name) {
        Logger::getInstance().log("Midshipman " + name + " created");
    }
};



#endif //STARWARSSIMULATION_MIDSHIPMAN_H
