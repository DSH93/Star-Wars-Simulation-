//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_IMPERIALAGENT_H
#define STARWARSSIMULATION_IMPERIALAGENT_H


#include <string>
#include <stdexcept>

class ImperialAgent {
protected:
    std::string name;

public:
    ImperialAgent(const std::string& agent_name) : name(agent_name) {
        if (name.length() > 16) {
            throw std::length_error("Agent name cannot exceed 16 characters");
        }
    }
    std::string getName() const {
        return name;
    }
    friend std::ostream& operator<<(std::ostream& os, const ImperialAgent& agent);
    virtual void displayRank() const = 0;
    virtual ~ImperialAgent() = default;
};



#endif //STARWARSSIMULATION_IMPERIALAGENT_H
