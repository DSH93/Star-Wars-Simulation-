//
// Created by Dor Shukrun on 29/08/2024.
//

#ifndef STARWARSSIMULATION_CONCRETEIMPERIALAGENTFACTORY_H
#define STARWARSSIMULATION_CONCRETEIMPERIALAGENTFACTORY_H

#include <memory>
#include "ImperialAgentFactory.h"
#include "Midshipman.h"
#include "Commander.h"
#include "Admiral.h"

/**
 * @class ConcreteImperialAgentFactory
 * @brief Implements the ImperialAgentFactory interface for creating specific ImperialAgent objects.
 */
class ConcreteImperialAgentFactory : public ImperialAgentFactory {
public:
    /**
     * @brief Creates a Midshipman agent.
     * @param name The name of the Midshipman.
     * @return A shared pointer to the created Midshipman.
     */
    [[nodiscard]] std::shared_ptr<ImperialAgent> createMidshipman(const std::string name) const override {
        return std::make_shared<Midshipman>(name);
    }

    /**
     * @brief Creates a Commander agent.
     * @param name The name of the Commander.
     * @return A shared pointer to the created Commander.
     */
    [[nodiscard]] std::shared_ptr<ImperialAgent> createCommander(const std::string name) const override {
        return std::make_shared<Commander>(name);
    }

    /**
     * @brief Creates an Admiral agent.
     * @param name The name of the Admiral.
     * @return A shared pointer to the created Admiral.
     */
    [[nodiscard]] std::shared_ptr<ImperialAgent> createAdmiral(const std::string name) const override {
        return std::make_shared<Admiral>(name);
    }
};

#endif //STARWARSSIMULATION_CONCRETEIMPERIALAGENTFACTORY_H
