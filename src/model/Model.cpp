#include "model/Model.h"
#include <algorithm>
#include <chrono>
#include <thread>


Model::Model() {
    defaultSite();

}

Model &Model::getInstance() {
    static Model instance;
    return instance;
}

float Model::calculateDistance(const Position &pos1, const Position &pos2) {
    return Position::distance(pos1, pos2);

}

void Model::advanceTime() {
    Timer::advanceTick();
    for (const std::string &id: ids) {
        objectsMap[id]->advanceTime();
        objectsMap[id]->update();
    }
}

void Model::logAndReportError(const std::string& errorMessage) {
    std::cerr << "Error: " << errorMessage << std::endl;
    Logger::getInstance().log(errorMessage, Logger::Level::ERROR);
}

bool Model::validateAndInsertId(const std::string& name) {
    if (uniqueIds.find(name) != uniqueIds.end()) {
        logAndReportError("Object with the same name already exists");
        return false;
    }
    uniqueIds.insert(name);
    return true;
}

std::unique_ptr<SpaceObject> Model::createSite(const std::string& type, int crystals, int production, Position pos, const std::string& name) {
    if (type == COMMAND_STATION) {
        return std::make_unique<SpaceStation>(crystals, production, pos, name);
    } else if (type == COMMAND_FORTRESS) {
        return std::make_unique<FortressStar>(crystals, pos, name);
    }
    logAndReportError("Invalid site type: " + type);
    return nullptr;
}

void Model::addSite(const std::vector<std::string> &command) {
    const std::string& name = command[1];
    float x = std::stof(command[2]);
    float y = std::stof(command[3]);
    Position pos(x, y);
    int crystalsAmount = std::stoi(command[4]);
    int productionRate = (command.size() > 5) ? std::stoi(command[5]) : 0;
    std::unique_ptr<SpaceObject> newSite;
    newSite = createSite(command[0], crystalsAmount, productionRate, pos, name);

    if (newSite) {
        sitesNumber++;
        sites.push_back(name);
        if (!validateAndInsertId(name)) return;
        ids.push_back(name);

        objectsMap[name] = std::shared_ptr<SpaceObject>(std::move(newSite));
    } else {
        logAndReportError("Invalid site type");
    }
}

void Model::createAgent(const std::string& agentType, const std::string& agentName, ConcreteImperialAgentFactory& factory) {
    if (agentType == "admiral") {
        agents[agentName] = factory.createAdmiral(agentName);
    } else if (agentType == "commander") {
        agents[agentName] = factory.createCommander(agentName);
    } else if (agentType == "midshipman") {
        agents[agentName] = factory.createMidshipman(agentName);
    }
}

void Model::createTroops(const std::vector<std::string> &command) {
    ConcreteImperialAgentFactory factory;
    createAgent(command[1], command[2], factory);
}

void Model::createSpaceship(const std::vector<std::string> &command) {
    const std::string &type = command[1]; // (destroyer, bomber, falcon, shuttle)
    const std::string& spaceshipName = command[2];
    std::vector<std::shared_ptr<SpaceObject>> patrolSites = collectPatrolSites();

    if (type == "falcon") {
        createFalcon(command, spaceshipName, patrolSites);
    } else {
        createSpaceshipWithPilot(command, type, spaceshipName, patrolSites);
    }
}

std::vector<std::shared_ptr<SpaceObject>> Model::collectPatrolSites() {
    std::vector<std::shared_ptr<SpaceObject>> patrolSites;
    for (auto &site : sites) {
        auto siteObj = std::dynamic_pointer_cast<SpaceObject>(objectsMap[site]);
        patrolSites.push_back(siteObj);
    }
    return patrolSites;
}

void Model::createFalcon(const std::vector<std::string> &command, const std::string &name,
                         const std::vector<std::shared_ptr<SpaceObject>> &patrolSites) {
    Position pos(std::stof(command[3]), std::stof(command[4]));
    auto falcon = std::make_unique<Falcon>(pos, name, patrolSites);
    if (!validateAndInsertId(name)) return;
    ids.push_back(name);
    falcons.push_back(name);
    objectsMap[name] = std::move(falcon);
}

void Model::createSpaceshipWithPilot(const std::vector<std::string> &command, const std::string &type,
                                     const std::string &name, const std::vector<std::shared_ptr<SpaceObject>> &patrolSites) {
    auto it = agents.find(command[3]);
    if (it == agents.end()) {
        logAndReportError("Pilot not found in agents");
        return;
    }
    Position pos(std::stof(command[4]), std::stof(command[5]));
    if (type == "destroyer") {
        createDestroyer(it->second, pos, name, patrolSites);
    } else if (type == "bomber") {
        createBomber(it->second, pos, name, patrolSites);
    } else if (type == "shuttle") {
        createShuttle(it->second, pos, name, patrolSites);
    }
}

void Model::createDestroyer(const std::shared_ptr<ImperialAgent> &pilot, const Position &pos,
                            const std::string &name, const std::vector<std::shared_ptr<SpaceObject>> &patrolSites) {
    auto admiralPilot = std::dynamic_pointer_cast<Admiral>(pilot);
    if (!admiralPilot) {
        logAndReportError("Pilot is not an Admiral for StarDestroyer");
        return;
    }
    // ,const std::shared_ptr<Admiral>& pilot = nullptr, const std::vector<std::shared_ptr<SpaceObject>>& sites
    auto destroyer = std::make_unique<StarDestroyer>(pos, name, DEFAULT_STAR_DESTROYER_SPEED, admiralPilot, patrolSites);
    if (!validateAndInsertId(name)) return;
    ids.push_back(name);
    starDestroyersSpaceships.push_back(name);
    objectsMap[name] = std::move(destroyer);
}

void Model::createBomber(const std::shared_ptr<ImperialAgent> &pilot, const Position &pos,
                         const std::string &name, const std::vector<std::shared_ptr<SpaceObject>> &patrolSites) {
    auto commanderPilot = std::dynamic_pointer_cast<Commander>(pilot);
    if (!commanderPilot) {
        logAndReportError("Pilot is not a Commander for TIEBomber");
        return;
    }
    auto bomber = std::make_unique<TIEBomber>(pos, name, DEFAULT_TIE_BOMBER_SPEED, commanderPilot, patrolSites);
    if (!validateAndInsertId(name)) return;
    ids.push_back(name);
    objectsMap[name] = std::move(bomber);
}

void Model::createShuttle(const std::shared_ptr<ImperialAgent> &pilot, const Position &pos,
                          const std::string &name, const std::vector<std::shared_ptr<SpaceObject>> &patrolSites) {
    auto midshipmanPilot = std::dynamic_pointer_cast<Midshipman>(pilot);
    if (!midshipmanPilot) {
        logAndReportError("Pilot is not a Midshipman for Shuttle");
        return;
    }
    auto shuttle = std::make_unique<Shuttle>(pos, name, DEFAULT_SHUTTLE_SPEED, midshipmanPilot, patrolSites);
    if (!validateAndInsertId(name)) return;
    ids.push_back(name);
    objectsMap[name] = std::move(shuttle);
}

void Model::create(const std::vector<std::string> &command) {
    if (command[1] == "admiral" || command[1] == "commander" || command[1] == "midshipman") {
        createTroops(command);
    } else if (command[1] == "destroyer" || command[1] == "bomber" || command[1] == "falcon" ||
               command[1] == "shuttle") {
        createSpaceship(command);
    }
}

void Model::statusByObj(const std::vector<std::string> &command) {
    const std::string &objectName = command[1];
    for (const std::string &id: ids) {
        if (id == objectName) objectsMap[id]->status();
    }
}

void Model::starDestroyerUpdate() {
    std::vector<std::pair<std::string, Position>> falconsPositions;
    for (const auto &falconName: falcons) {
        auto falcon = std::dynamic_pointer_cast<Falcon>(objectsMap[falconName]);
        if (!falcon->isAlive()) continue;
        falconsPositions.emplace_back(falconName, falcon->getCurrentPosition());
    }
    std::string falconName;
    for (const auto &starDestroyerName: starDestroyersSpaceships) {
        auto starDestroyer = std::dynamic_pointer_cast<StarDestroyer>(objectsMap[starDestroyerName]);
        falconName = starDestroyer->missileUpdate(falconsPositions);
        if (!falconName.empty()) {
            auto falcon = std::dynamic_pointer_cast<Falcon>(objectsMap[falconName]);
            falcon->killFalcon();
        }
    }

}

bool Model::validateObjectExists(const std::string &objectName) {
    if (objectsMap.find(objectName) == objectsMap.end()) {
        logAndReportError("Object '" + objectName +"' not found");
        return false;
    }
    return true;
}

bool Model::validateObjectExists(const std::string &objectName, const std::string &role) {
    if (objectsMap.find(objectName) == objectsMap.end()) {
        logAndReportError(role + " '" + objectName + "' not found");
        return false;
    }
    return true;
}

float Model::findClosetBomber(const Position &attackerPos) {
    float ClosetBomber = MAX_DISTANCE;
    for (const std::string &bomberName: starDestroyersSpaceships) {
        auto bomber = std::dynamic_pointer_cast<TIEBomber>(objectsMap[bomberName]);
        if (bomber) {
            Position bomberPos = bomber->getCurrentPosition();
            float distanceFromBomber = calculateDistance(bomberPos, attackerPos);
            if (distanceFromBomber < ClosetBomber) ClosetBomber = distanceFromBomber;
        }
    }
    return ClosetBomber;

}

void Model::printStatusByType(const std::string &title, const std::vector<std::string> &names, const std::unordered_set<std::string> &types) {
    std::cout << title << std::endl;
    for (const auto &id : names) {
        auto obj = objectsMap[id];
        if (types.find(obj->getType()) != types.end()) {
            obj->status();
        }
    }
}

void Model::statusCMD() {
    const std::unordered_set<std::string> sitesTitle = {"SpaceStation", "fortressStar"};
    const std::unordered_set<std::string> falconsTitle = {"Falcon"};
    const std::unordered_set<std::string> spaceFleetTitle = {"StarDestroyer", "TIEBomber", "Shuttle", "Missile"};

    std::cout << std::endl;
    std::cout << std::endl;
    printStatusByType("SPACE STATIONS AND FORTRESS", sites, sitesTitle);
    std::cout << std::endl;
    std::cout << std::endl;
    printStatusByType("THE REBELS FALCONS", falcons, falconsTitle);
    std::cout << std::endl;
    std::cout << std::endl;
    printStatusByType("THE EMPEROR'S SPACE FLEET", ids, spaceFleetTitle);
    std::cout << std::endl;
    std::cout << std::endl;
}

void Model::goCMD() {
    advanceTime();
    Logger::getInstance().log("======================== TIME: [ " + std::to_string(Timer::getCurrentTick()) + " ] ========================");
    starDestroyerUpdate();

}

void Model::attackCMD(const std::vector<std::string> &command) {
    const std::string &attackerName = command[0]; // falcon
    const std::string &targetName = command[2]; // shuttle
    if (!validateObjectExists(attackerName) || !validateObjectExists(targetName)) return; // invalid object
    auto attacker = std::dynamic_pointer_cast<Falcon>(objectsMap[attackerName]);
    auto target = std::dynamic_pointer_cast<Shuttle>(objectsMap[targetName]);
    if (!attacker || !target){
        logAndReportError("Invalid attacker or target object");
        return;
    }

    Position attackerPos = attacker->getCurrentPosition();
    Position targetPos = target->getCurrentPosition();
    float distanceToTarget = calculateDistance(attackerPos, targetPos);
    float closetBomber = findClosetBomber(attackerPos);
    attacker->attack(target, distanceToTarget, closetBomber); // falcon attack shuttle

}

void Model::shootCMD(const std::vector<std::string> &command) {
    const std::string &bomber = command[0]; // bomber
    Position targetPos(std::stof(command[2]), std::stof(command[3])); // target positionCMD
    if (!validateObjectExists(bomber)) return; // invalid object
    auto starDestroyer = std::dynamic_pointer_cast<StarDestroyer>(objectsMap[bomber]);
    if (!starDestroyer){
        logAndReportError("Invalid starDestroyer object");
        return;
    }
    starDestroyer->shoot(targetPos);
}

void Model::stopCMD(const std::vector<std::string> &command) {
    const std::string &spaceshipName = command[0];
    if (!validateObjectExists(spaceshipName)) return; // invalid object
    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    if (!spaceship) {
        logAndReportError("Invalid spaceship object");
        return; // invalid cast
    }
    spaceship->stop();

}

void Model::positionCMD(const std::vector<std::string> &command) { // positionCMD Command
    const std::string &spaceshipName = command[0];
    float x = std::stof(command[2]);
    float y = std::stof(command[3]);
    if (!validateObjectExists(spaceshipName)) return; // Validate object existence
    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    if (!spaceship){
        logAndReportError("Invalid spaceship object");
        return; // Validate cast
    }
    spaceship->setDestinationByPosition(Position(x, y));
}

void Model::destinationCMD(const std::vector<std::string> &command) { // destinationCMD Command
    const std::string &spaceshipName = command[0];
    const std::string &siteName = command[2];
    if (!validateObjectExists(spaceshipName) || !validateObjectExists(siteName, "site")) return; // invalid object
    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    auto site = std::dynamic_pointer_cast<SpaceObject>(objectsMap[siteName]);
    if (!spaceship || !site){
        logAndReportError("Invalid spaceship or site object");
        return; // invalid cast
    }

    spaceship->setSiteDestination(siteName);


}

void Model::courseCMD(const std::vector<std::string> &command) {
    const std::string &spaceshipName = command[0];
    if (!validateObjectExists(spaceshipName)) return; // invalid object

    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    if (!spaceship) return; // invalid cast

    float angle = std::stof(command[2]);
    if (command.size() > 3) {
        auto speed = (float) std::stoi(command[3]);
        for (const auto &falcon: falcons) {
            auto falconObj = std::dynamic_pointer_cast<Falcon>(objectsMap[falcon]);
            if (falconObj) {
                falconObj->setSpeed(speed);
            }

        }
    }
    spaceship->setCourse(angle);
}

void Model::defaultSite() {
    std::vector<std::string> command = {"fortress", "DS", "40.00", "10.00", "100000", "0"};
    addSite(command); // initialize the fortress

}

void Model::SupplyCMD(const std::vector<std::string> &command) {
    const std::string &shuttleName = command[0];
    const std::string &spaceStationName = command[2]; // station site
    const std::string &fortressName = command[3]; // next fortress site

    if (!validateObjectExists(shuttleName) || !validateObjectExists(spaceStationName, "site") ||
        !validateObjectExists(fortressName, "site")) return; // invalid object

    auto shuttle = std::dynamic_pointer_cast<Shuttle>(objectsMap[shuttleName]);
    auto spaceStation = std::dynamic_pointer_cast<SpaceStation>(objectsMap[spaceStationName]);
    auto fortress = std::dynamic_pointer_cast<FortressStar>(objectsMap[fortressName]);

    if (!spaceStation || !fortress || !shuttle) {
        logAndReportError("Invalid shuttle, spaceStation or fortress object");
        return; // invalid cast
    }

    auto mission = std::make_pair(spaceStation, fortress);
    shuttle->addSupplyMission(mission);
}

std::vector<std::pair<std::string, Position>> Model::getPositions() const {
    std::vector<std::pair<std::string, Position>> positions;
    for (const std::string &id: ids) {
        auto object = Model::getInstance().objectsMap[id];
        auto spaceship = std::dynamic_pointer_cast<Spaceship>(object);
        if (spaceship) {
            if (spaceship->isAlive()) {
                positions.emplace_back(id, object->getPosition());
                auto starDestroyer = std::dynamic_pointer_cast<StarDestroyer>(object);
                if (starDestroyer) {
                    for (const auto &missile: starDestroyer->getMissilesNameAndPosition()) {
                        std::string missileName = missile.first;
                        Position missilePos = missile.second;
                        positions.emplace_back(missileName, missilePos);
                    }
                }
            }
        } else {
            positions.emplace_back(id, object->getPosition());
        }

    }
    return positions;
}

std::shared_ptr<SpaceObject> Model::getObject(const std::string &objName) const {
    auto obj = objectsMap.find(objName);
    if (obj != objectsMap.end()){
        return obj->second;
    }
    logAndReportError("Object '" + objName + "' not found");
    return nullptr;
}

void Model::clearAllStationsAndFortresses() { // clear all stations and fortresses
    for (const auto &site: sites) {
        objectsMap.erase(site);
    }
    sites.clear();
    uniqueIds.clear();
    sitesNumber = 0;

}
