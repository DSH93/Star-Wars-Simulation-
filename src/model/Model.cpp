//
// Created by Dor Shukrun on 23/08/2024.
//

#include "model/Model.h"





Model::Model() {
    std::vector<std::string> command;
    command.emplace_back("fortress"); // adding a default fortress DS at (40, 10) with 100000 crystals
    command.emplace_back("DS"); // name
    command.emplace_back("40.00"); // x
    command.emplace_back("10.00"); // y
    command.emplace_back("100000"); // crystalsAmount
    command.emplace_back("0"); // productionRate
    addSite(command); // initialize the fortress
}

Model &Model::getInstance() {
    static Model instance;
    return instance;
}


void Model::removeObject(const SpaceObject &object) {
    std::string id = object.getId();

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if ((*it)->getId() == object.getId()) {
            objects.erase(it);
            break;
        }
    }

}

float Model::calculateDistance(const Position &pos1, const Position &pos2) {
    return pos1.distance(pos2);

}

Direction Model::calculateDirection(const Position &from, const Position &to) {
    Direction direction(from, to);
    return direction;
}

void Model::advanceTime() {
    Timer::advanceTick();
    for (auto &object: objects) {
        object->update();
    }

}

int Model::getCurrentTime() {
    return Timer::getCurrentTick();
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
        objectsMap[name] = std::shared_ptr<SpaceStation>(static_cast<SpaceStation*>(newSite.get()), [](SpaceObject*){});
    } else if (command[0] == "fortress") {
        newSite = std::make_unique<FortressStar>(crystalsAmount, pos, name);
        objectsMap[name] = std::shared_ptr<FortressStar>(static_cast<FortressStar*>(newSite.get()), [](SpaceObject*){});
    }
    if (newSite) {
        objects.push_back(std::move(newSite));
    } else {
        std::cerr << "Error: Invalid site type" << std::endl;
    }
}


void Model::createTroops(std::vector<std::string> &command) {
    std::string imperialAgentName = command[2];
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
    std::string type = command[1]; //  (destroyer, bomber, falcon, shuttle)
    std::string spaceshipName = command[2];

    if (type == "falcon") {
        //  Millennium Falcon
        Position pos(std::stof(command[3]), std::stof(command[4]));
        auto falcon = std::make_unique<MillenniumFalcon>(pos, spaceshipName);
        objects.push_back(std::move(falcon));
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
                objects.push_back(std::move(destroyer));

            } else if (type == "bomber") {
                bombers.push_back(command[2]);
                auto commanderPilot = std::dynamic_pointer_cast<Commander>(it->second);
                if (!commanderPilot) {
                    std::cerr << "Error: pilot is not a Commander for TIEBomber" << std::endl;
                    return;
                }
                auto bomber = std::make_unique<TIEBomber>(pos1, spaceshipName, 1000.0f, commanderPilot);
                objects.push_back(std::move(bomber));

            } else if (type == "shuttle") {
                auto midshipmanPilot = std::dynamic_pointer_cast<Midshipman>(it->second);
                if (!midshipmanPilot) {
                    std::cerr << "Error: pilot is not a Midshipman for Shuttle" << std::endl;
                    return;
                }
                auto shuttle = std::make_unique<Shuttle>(pos1, spaceshipName, 500.0f, midshipmanPilot);
                objects.push_back(std::move(shuttle));
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
    std::cout << "Current time: " << Timer::getCurrentTick() << std::endl;
    std::cout << "status: " << std::endl;

    for (auto &object: objects) {
        object->status();
    }

}

void Model::go() {
    std::cout << "go" << std::endl;
    advanceTime();

}

void Model::attack(std::vector<std::string> &command) {
    std::string attackerName = command[0];
    std::string targetName = command[2];

    std::shared_ptr<SpaceObject> attacker = nullptr;
    std::shared_ptr<SpaceObject> target = nullptr;

    for (const auto& object : objects) {
        if (object->getId() == attackerName) {
            attacker = std::shared_ptr<SpaceObject>(object.get(), [](SpaceObject*){});
            break;
        }
    }

    for (const auto& object : objects) {
        if (object->getId() == targetName) {
            target = std::shared_ptr<SpaceObject>(object.get(), [](SpaceObject*){});
            break;
        }
    }

    if (!attacker) {
        std::cerr << "Error: Attacker '" << attackerName << "' not found" << std::endl;
        return;
    }
    if (!target) {
        std::cerr << "Error: Target '" << targetName << "' not found" << std::endl;
        return;
    }

    Position attackerPos = attacker->getCurrentPosition();
    Position targetPos = target->getCurrentPosition();
    float distance = calculateDistance(attackerPos, targetPos);
    if (distance > 100000) {
        std::cerr << "Error: Target is too far for attack" << std::endl;
        return;
    }






}



void Model::shoot(std::vector<std::string> &command) {

}

void Model::stop(std::vector<std::string> &command) {

}

void Model::position(std::vector<std::string> &command) {

}

void Model::destination(std::vector<std::string> &command) {

}

void Model::exit() {

}

void Model::course() {

}
