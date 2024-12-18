//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_COMMANDER_H
#define STARWARSSIMULATION_COMMANDER_H

#include "ImperialAgent.h"
#include "Logger.h"

/**
 * @class Commander
 * @brief Represents a Commander in the Imperial fleet.
 *
 * The Commander class inherits from ImperialAgent and logs its creation.
 */
class Commander : public ImperialAgent {
public:
    /**
     * @brief Constructs a Commander object with a given name.
     * @param name The name of the Commander.
     */
    explicit Commander(const std::string& name) : ImperialAgent(name) {
        Logger::getInstance().log("Commander " + name + " was created");
    }
};

#endif //STARWARSSIMULATION_COMMANDER_H
