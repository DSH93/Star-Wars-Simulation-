//
// Created by Dor Shukrun on 28/08/2024.
//

#ifndef STARWARSSIMULATION_IMPERIALAGENTFACTORY_H
#define STARWARSSIMULATION_IMPERIALAGENTFACTORY_H

#include <memory>
#include "ImperialAgent.h"

class ImperialAgentFactory {
public:
    virtual std::shared_ptr<ImperialAgent> createMidshipman(const std::string name) const = 0;
    virtual std::shared_ptr<ImperialAgent> createCommander(const std::string name) const = 0;
    virtual std::shared_ptr<ImperialAgent> createAdmiral(const std::string name) const = 0;
    virtual ~ImperialAgentFactory() = default;
};


#endif //STARWARSSIMULATION_IMPERIALAGENTFACTORY_H
