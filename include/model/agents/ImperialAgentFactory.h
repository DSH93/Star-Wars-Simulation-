//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_IMPERIALAGENTFACTORY_H
#define STARWARSSIMULATION_IMPERIALAGENTFACTORY_H

#include <memory>
#include <string>
#include "ImperialAgent.h"

/**
 * @class ImperialAgentFactory
 * @brief Abstract factory interface for creating different types of Imperial Agents.
 *
 * This class defines a standard interface for creating instances of different types
 * of Imperial Agents, such as Midshipman, Commander, and Admiral.
 */
class ImperialAgentFactory {
public:
    /**
     * @brief Creates a Midshipman agent.
     * @param name The name of the Midshipman.
     * @return A shared pointer to the created Midshipman.
     *
     * @note The name must conform to the length constraints of ImperialAgent.
     */
    [[nodiscard]] virtual std::shared_ptr<ImperialAgent> createMidshipman(std::string name) const = 0;

    /**
     * @brief Creates a Commander agent.
     * @param name The name of the Commander.
     * @return A shared pointer to the created Commander.
     *
     * @note The name must conform to the length constraints of ImperialAgent.
     */
    [[nodiscard]] virtual std::shared_ptr<ImperialAgent> createCommander(std::string name) const = 0;

    /**
     * @brief Creates an Admiral agent.
     * @param name The name of the Admiral.
     * @return A shared pointer to the created Admiral.
     *
     * @note The name must conform to the length constraints of ImperialAgent.
     */
    [[nodiscard]] virtual std::shared_ptr<ImperialAgent> createAdmiral(std::string name) const = 0;

    /**
     * @brief Virtual destructor for the ImperialAgentFactory.
     */
    virtual ~ImperialAgentFactory() = default;
};

#endif //STARWARSSIMULATION_IMPERIALAGENTFACTORY_H
