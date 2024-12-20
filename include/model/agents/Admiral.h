//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_ADMIRAL_H
#define STARWARSSIMULATION_ADMIRAL_H

#include "ImperialAgent.h"
#include "Logger.h"

/**
 * @class Admiral
 * @brief Represents an Admiral in the Imperial fleet.
 *
 * The Admiral class inherits from ImperialAgent and logs its creation.
 */
class Admiral : public ImperialAgent {
public:
    /**
     * @brief Constructs an Admiral object with a given name.
     * @param name The name of the Admiral.
     */
    explicit Admiral(const std::string& name) : ImperialAgent(name) {
        Logger::getInstance().log("Admiral " + name + " created", Logger::Level::INFO);
    }
};

#endif //STARWARSSIMULATION_ADMIRAL_H
