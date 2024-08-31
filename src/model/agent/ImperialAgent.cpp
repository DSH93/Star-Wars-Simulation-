//
// Created by Dor Shukrun on 29/08/2024.
//



#include <ostream>
#include "model/agents/ImperialAgent.h"

std::ostream& operator<<(std::ostream& os, const ImperialAgent& agent) {
    os << agent.getName();
    return os;
}
