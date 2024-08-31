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


class ConcreteImperialAgentFactory : public ImperialAgentFactory {
public:
    std::shared_ptr<ImperialAgent> createMidshipman(const std::string name) const override {
        return std::make_shared<Midshipman>(name);
    }

    std::shared_ptr<ImperialAgent> createCommander(const std::string name) const override {
        return std::make_shared<Commander>(name);
    }

    std::shared_ptr<ImperialAgent> createAdmiral(const std::string name) const override {
        return std::make_shared<Admiral>(name);
    }
};


#endif //STARWARSSIMULATION_CONCRETEIMPERIALAGENTFACTORY_H
