//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_IMPERIALAGENT_H
#define STARWARSSIMULATION_IMPERIALAGENT_H

#include <string>
#include <stdexcept>
#include <ostream>
#include <utility>
#include "Logger.h" // Include Logger for logging errors

/**
 * @class ImperialAgent
 * @brief Base class representing an Imperial Agent in the Star Wars Simulation.
 *
 * This class provides common functionality for all types of Imperial Agents, including
 * name validation and a standardized interface for derived classes.
 */
class ImperialAgent {
protected:
    std::string name; ///< The name of the Imperial Agent (maximum 16 characters).

public:
    /**
     * @brief Constructs an ImperialAgent with the specified name.
     * @param agent_name The name of the agent. Must not exceed 16 characters.
     *
     * @throws std::length_error If the name exceeds 16 characters.
     */
    explicit ImperialAgent(std::string agent_name) : name(std::move(agent_name)) {
        if (name.length() > 16) {
            Logger::getInstance().log("Agent name cannot exceed 16 characters: " + agent_name, Logger::Level::ERROR);
            throw std::length_error("Agent name cannot exceed 16 characters");
        }
    }

    /**
     * @brief Retrieves the name of the agent.
     * @return The name of the agent as a string.
     */
    [[nodiscard]] std::string getName() const {
        return name;
    }

    /**
     * @brief Overloads the stream insertion operator to print the agent's name.
     * @param os The output stream.
     * @param agent The ImperialAgent object.
     * @return A reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ImperialAgent& agent) {
        os << agent.getName();
        return os;
    }

    /**
     * @brief Virtual destructor for the ImperialAgent class.
     */
    virtual ~ImperialAgent() = default;
};

#endif //STARWARSSIMULATION_IMPERIALAGENT_H
