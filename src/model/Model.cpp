//
// Created by Dor Shukrun on 23/08/2024.
//

#include "model/Model.h"
#include <algorithm>



Model::Model() {
    defaultSite();

}

Model &Model::getInstance() {
    static Model instance;
    return instance;
}

void Model::removeObject(const SpaceObject &object) {
    std::string objectName = object.getId();

    for (const std::string& id: ids) {
        if (id == objectName) {
            objectsMap.erase(objectName);
            ids.erase(std::remove(ids.begin(), ids.end(), objectName), ids.end());

            break;
        }
    }

}

float Model::calculateDistance(const Position &pos1, const Position &pos2) {
    return pos1.distance(pos2);

}

void Model::advanceTime() {
    Timer::advanceTick();
    for (const std::string& id: ids) {
        objectsMap[id]->advanceTime();
        objectsMap[id]->update();
    }

}

void Model::addSite(std::vector<std::string> &command) {
    std::string name = command[1];
    float x = std::stof(command[2]);
    float y = std::stof(command[3]);
    Position pos(x, y);
    int crystalsAmount = std::stoi(command[4]);
    int productionRate = (command.size() > 5) ? std::stoi(command[5]) : 0;
    std::unique_ptr<SpaceObject> newSite;

    if (command[0] == "station") {
        newSite = std::make_unique<SpaceStation>(crystalsAmount, productionRate, pos, name);
    } else if (command[0] == "fortress") {
        newSite = std::make_unique<FortressStar>(crystalsAmount, pos, name);
    }

    if (newSite) {
        ids.push_back(name);
        objectsMap[name] = std::shared_ptr<SpaceObject>(std::move(newSite));
    } else {
        std::cerr << "Error: Invalid site type" << std::endl;
    }
}

void Model::createTroops(std::vector<std::string> &command) {
    const std::string& imperialAgentName = command[2];
    ConcreteImperialAgentFactory factory;

    if (command[1] == "admiral") {
        auto admiral = factory.createAdmiral(imperialAgentName);
        agents[imperialAgentName] = std::move(admiral);

    } else if (command[1] == "commander") {
        auto commander = factory.createCommander(imperialAgentName);
        agents[imperialAgentName] = std::move(commander);


    } else if (command[1] == "midshipman") {
        auto midshipman = factory.createMidshipman(imperialAgentName);
        agents[imperialAgentName] = std::move(midshipman);

    }
}

void Model::createSpaceship(std::vector<std::string> &command) {
    const std::string& type = command[1]; //  (destroyer, bomber, falcon, shuttle)
    std::string spaceshipName = command[2];

    if (type == "falcon") {
        //  Millennium Falcon
        Position pos(std::stof(command[3]), std::stof(command[4]));
        auto falcon = std::make_unique<Falcon>(pos, spaceshipName);
        ids.push_back(spaceshipName);
        falcons.push_back(spaceshipName);
        objectsMap[spaceshipName] = std::move(falcon);
    } else {

        auto it = agents.find(command[3]);
        if (it != agents.end()) {
            Position pos1(std::stof(command[4]), std::stof(command[5]));

            if (type == "destroyer") {

                auto admiralPilot = std::dynamic_pointer_cast<Admiral>(it->second);
                if (!admiralPilot) {
                    std::cerr << "Error: pilot is not an Admiral for StarDestroyer" << std::endl;
                    return;
                }
                auto destroyer = std::make_unique<StarDestroyer>(pos1, spaceshipName, 2000.0f, admiralPilot);
                ids.push_back(spaceshipName);
                starDestroyersSpaceships.push_back(command[2]);

                objectsMap[spaceshipName] = std::move(destroyer);

            } else if (type == "bomber") {
                auto commanderPilot = std::dynamic_pointer_cast<Commander>(it->second);
                if (!commanderPilot) {
                    std::cerr << "Error: pilot is not a Commander for TIEBomber" << std::endl;
                    return;
                }
                auto bomber = std::make_unique<TIEBomber>(pos1, spaceshipName, 1000.0f, commanderPilot);
                ids.push_back(spaceshipName);
                objectsMap[spaceshipName] = std::move(bomber);

            } else if (type == "shuttle") {
                auto midshipmanPilot = std::dynamic_pointer_cast<Midshipman>(it->second);
                if (!midshipmanPilot) {
                    std::cerr << "Error: pilot is not a Midshipman for Shuttle" << std::endl;
                    return;
                }
                auto shuttle = std::make_unique<Shuttle>(pos1, spaceshipName, 500.0f, midshipmanPilot);
                ids.push_back(spaceshipName);
                objectsMap[spaceshipName] = std::move(shuttle);
            }
        } else {
            std::cerr << "Error: Pilot not found in agents" << std::endl;
        }
    }
}

void Model::create(std::vector<std::string> &command) {
    if (command[1] == "admiral" || command[1] == "commander" || command[1] == "midshipman") {
        createTroops(command);
    } else if (command[1] == "destroyer" || command[1] == "bomber" || command[1] == "falcon" ||
               command[1] == "shuttle") {
        createSpaceship(command);
    }
}

void Model::status() {
    for (const std::string& id: ids) {
        objectsMap[id]->status();
    }
}

void Model::statusByObj(std::vector<std::string> &command) {
    const std::string& objectName = command[1];
    for (const std::string& id: ids) {
        if (id == objectName) objectsMap[id]->status();
    }
}

void Model::starDestroyerUpdate() {
    std::vector<std::pair<std::string, Position>> falconsPositions;
    for (const auto& falconName: falcons) { // todo check for falcons if its updated
        auto falcon = std::dynamic_pointer_cast<Falcon>(objectsMap[falconName]);
        if (!falcon->isAlive()) continue;
        falconsPositions.emplace_back(falconName, falcon->getCurrentPosition());
    }
    std::string falconName;
    for (const auto& starDestroyerName: starDestroyersSpaceships) {
        auto starDestroyer = std::dynamic_pointer_cast<StarDestroyer>(objectsMap[starDestroyerName]);
        falconName = starDestroyer->missileUpdate(falconsPositions);
    }
    if (!falconName.empty()) {
        auto falcon = std::dynamic_pointer_cast<Falcon>(objectsMap[falconName]);
        falcon->killFalcon();

    }
}

void Model::go() {
    advanceTime();
    starDestroyerUpdate();




}

bool Model::validateObjectExists(const std::string &objectName) {
    if (objectsMap.find(objectName) == objectsMap.end()) {
        std::cerr << "Error: Object '" << objectName << "' not found" << std::endl;
        return false;
    }
    return true;
}

bool Model::validateObjectExists(const std::string &objectName, const std::string &role) {
    if (objectsMap.find(objectName) == objectsMap.end()) {
        std::cerr << "Error: " << role << " '" << objectName << "' not found" << std::endl;
        return false;
    }
    return true;
}

float Model::findClosetBomber(const Position &attackerPos) {
    float ClosetBomber = 1000000; // 1000Km
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

void Model::attack(std::vector<std::string> &command) {
    const std::string& attackerName = command[0]; // falcon
    const std::string& targetName = command[2]; // shuttle
    if (!validateObjectExists(attackerName) || !validateObjectExists(targetName)) return; // invalid object
    auto attacker = std::dynamic_pointer_cast<Falcon>(objectsMap[attackerName]);
    auto target = std::dynamic_pointer_cast<Shuttle>(objectsMap[targetName]);
    if (!attacker || !target) return; // invalid cast

    Position attackerPos = attacker->getCurrentPosition();
    Position targetPos = target->getCurrentPosition();
    float distanceToTarget = calculateDistance(attackerPos, targetPos);
    float closetBomber = findClosetBomber(attackerPos);
    attacker->attack(target, distanceToTarget, closetBomber); // falcon attack shuttle

}

void Model::shoot(std::vector<std::string> &command) {
    const std::string& bomber = command[0]; // bomber
    Position targetPos(std::stof(command[2]), std::stof(command[3])); // target position
    if (!validateObjectExists(bomber)) return; // invalid object
    auto starDestroyer = std::dynamic_pointer_cast<StarDestroyer>(objectsMap[bomber]);
    if (!starDestroyer) return; // invalid cast
    starDestroyer->shoot(targetPos);
}

void Model::stop(std::vector<std::string> &command) {
    const std::string& spaceshipName = command[0];
    if (!validateObjectExists(spaceshipName)) return; // invalid object
    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    if (!spaceship) return; // invalid cast
    spaceship->stop();

}

void Model::position(std::vector<std::string> &command) {
    const std::string& spaceshipName = command[0];
    float x = std::stof(command[1]);
    float y = std::stof(command[2]);
    float speed = (command.size() > 3) ? std::stof(command[3]) : 0.0f; // Extract speed if provided
    if (!validateObjectExists(spaceshipName)) return; // Validate object existence
    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    if (!spaceship) return; // Validate cast
    if (speed > 0.0f) spaceship->setSpeed(speed);
    spaceship->move(Position(x, y)); // Move spaceship
}

void Model::destination(std::vector<std::string> &command) {
    const std::string& spaceshipName = command[0];
    if (!validateObjectExists(spaceshipName)) return; // invalid object
    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    if (!spaceship) return; // invalid cast

    const std::string &siteName = command[2]; // fortress site
    if (!validateObjectExists(siteName, "site")) return; // invalid object
    auto site = std::dynamic_pointer_cast<SpaceObject>(objectsMap[siteName]);
    if (!site) return; // invalid cast
    spaceship->move(site->getPosition());


}

void Model::course(std::vector<std::string> &command) {
    const std::string& spaceshipName = command[0];
    if (!validateObjectExists(spaceshipName)) return; // invalid object
    auto spaceship = std::dynamic_pointer_cast<Spaceship>(objectsMap[spaceshipName]);
    if (!spaceship) return; // invalid cast

    float angle = std::stof(command[2]);
    spaceship->setDirection(Direction(angle));

    if (command.size() > 3) {
        auto speed = (float) std::stoi(command[3]);
        for(const auto& falcon: falcons) {
            falcon == spaceshipName ? spaceship->setSpeed(speed) : spaceship->setSpeed(3000.0f);

        }
    }


}

void Model::defaultSite() {
    std::vector<std::string> command;
    command.emplace_back("fortress"); // adding a default fortress DS at (40, 10) with 100000 crystals
    command.emplace_back("DS"); // name
    command.emplace_back("40.00"); // x
    command.emplace_back("10.00"); // y
    command.emplace_back("100000"); // crystalsAmount
    command.emplace_back("0"); // productionRate
    addSite(command); // initialize the fortress

}

void Model::addSupplyMission(std::vector<std::string> &command) {
    const std::string& shuttleName = command[0];
    const std::string& spaceStationName = command[2]; // station site
    const std::string& fortressName = command[3]; // next fortress site

    if (!validateObjectExists(shuttleName)) return; // invalid object
    auto shuttle = std::dynamic_pointer_cast<Shuttle>(objectsMap[shuttleName]);
    if (!shuttle) return; // invalid cast

    if (!validateObjectExists(spaceStationName, "site")) return; // invalid object
    auto spaceStation = std::dynamic_pointer_cast<SpaceStation>(objectsMap[spaceStationName]);
    if (!spaceStation) return; // invalid cast

    if (!validateObjectExists(fortressName, "site")) return; // invalid object
    auto fortress = std::dynamic_pointer_cast<FortressStar>(objectsMap[fortressName]);
    if (!fortress) return; // invalid cast
    auto mission = std::make_pair(spaceStation, fortress);
    shuttle->addSupplyMission(mission);
}

std::vector<std::pair<std::string, Position>> Model::getPositions() const {
    std::vector<std::pair<std::string, Position>> positions;
    for (const std::string& id: ids) {
        auto object = Model::getInstance().objectsMap[id];
        positions.emplace_back(id, object->getPosition());
        auto starDestroyer = std::dynamic_pointer_cast<StarDestroyer>(object);
        if (starDestroyer) {
            for (const auto& missile: starDestroyer->getMissilesNameAndPosition()) {
                std::string missileName = missile.first;
                Position missilePos = missile.second;
                positions.emplace_back(missileName, missilePos);
            }
        }

    }
    return positions;
}

