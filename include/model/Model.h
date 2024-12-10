//
// Created by Dor Shukrun on 23/08/2024.
//

#ifndef STARWARSSIMULATION_MODEL_H
#define STARWARSSIMULATION_MODEL_H

#include <memory>
#include "Position.h"
#include "Direction.h"
#include "SpaceObject.h"
#include <vector>
#include <set>
#include <unordered_map>
#include "SpaceObject.h"
#include "Timer.h"
#include "model/SpaceStation.h"
#include "model/FortressStar.h"
#include "model/spaceships/Spaceship.h"
#include "model/spaceships/StarDestroyer.h"
#include "model/spaceships/TIEBomber.h"
#include "model/spaceships/Falcon.h"
#include "model/spaceships/Shuttle.h"

#include "model/agents/ImperialAgent.h"
#include "model/agents/ImperialAgentFactory.h"
#include "model/agents/ConcreteImperialAgentFactory.h"
#include "model/agents/Commander.h"
#include "model/agents/Midshipman.h"
#include "model/agents/Admiral.h"
#include "model/spaceships/Missile.h"


class Model {
private:
    std::unordered_map<std::string, std::shared_ptr<SpaceObject>> objectsMap;
    std::unordered_map<std::string, std::shared_ptr<ImperialAgent>> agents;
    std::vector<std::string> ids;
    std::vector<std::string> starDestroyersSpaceships;
    std::vector<std::string> missiles;
    std::vector<std::string> falcons;

    Model(); // provide Singleton

public:
    static Model &getInstance(); // provide the only instance of Model
    Model(const Model &) = delete;
    Model &operator=(const Model &) = delete; // prevent copy and assignment
    void removeObject(const SpaceObject &object);
    static float calculateDistance(const Position &pos1, const Position &pos2);

    void addSite(std::vector<std::string> &command);
    void create(std::vector<std::string> &command);
    void status(); // display the status of all the objects
    void go(); // continue the simulation in 1 step of time
    void attack(std::vector<std::string> &command); // determine the target of a missile for the Falcon
    void shoot(std::vector<std::string> &command); // determine the target of a missile for the TIEBomber
    void stop(std::vector<std::string> &command); // to stop the movement of a spaceship and cancel all the waiting missions
    void position(std::vector<std::string> &command); // to determine the fortress of a flight
    void destination(std::vector<std::string> &command); // to determine the site destinatio
    void createTroops(std::vector<std::string> &command);
    void createSpaceship(std::vector<std::string> &command);
    void advanceTime();

    bool validateObjectExists(const std::string &objectName);
    bool validateObjectExists(const std::string &objectName, const std::string &role);
    float findClosetBomber(const Position &attackerPos);
    void course(std::vector<std::string> &command);
    void defaultSite();
    void starDestroyerUpdate();
    void addSupplyMission(std::vector<std::string> &command);

    void statusByObj(std::vector<std::string> &command);

    std::vector<std::pair<std::string, Position>> getPositions() const;
};


#endif //STARWARSSIMULATION_MODEL_H
