//
// Created by Dor Shukrun on 23/08/2024.
//

#include "model/Model.h"

Model::Model() {}

Model &Model::getInstance() {
    static Model instance;
    return instance;
}

void Model::addObject(std::unique_ptr<SpaceObject> object) {
    objects.push_back(std::move(object));
}

void Model::removeObject(const SpaceObject &object) {
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
    if (command[0] == "station") {
        std::string name = command[1];
        float x = std::stof(command[2]);
        float y = std::stof(command[3]);
        Position pos(x, y);
        int crystalsAmount = std::stoi(command[4]);
        int productionRate = std::stoi(command[5]);
        auto newStation = std::make_unique<SpaceStation>(crystalsAmount, productionRate, pos, name);
        newStation->toString();
        objects.push_back(std::move(newStation));

    } else if (command[0] == "fortress") {
        std::string name = command[1];
        float x = std::stof(command[2]);
        float y = std::stof(command[3]);
        Position pos(x, y);
        int crystalsAmount = std::stoi(command[4]);
        int productionRate = std::stoi(command[5]);
        int maxCapacity = std::stoi(command[6]);
        //FortressStar newFortress(crystalsAmount,pos, name);


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
    std::string type = command[1];
    std::string spaceshipName = command[2];


    if (type == "falcon") {
        Position pos(std::stof(command[3]), std::stof(command[4]));
        auto falcon = std::make_unique<MillenniumFalcon>(pos, spaceshipName);
        objects.push_back(std::move(falcon));

    } else {
        auto it = agents.find(command[3]);
        if (it != agents.end()) {
            auto pilot = std::move(it->second);
            Position pos1(std::stof(command[4]), std::stof(command[5]));
            if (type == "destroyer") {
                auto destroyer = std::make_unique<StarDestroyer>(pos1, spaceshipName, 2000.0f,
                                                                 std::dynamic_pointer_cast<Admiral>(pilot));
                objects.push_back(std::move(destroyer));


            } else if (type == "bomber") {
//            auto bomber = std::make_unique<TIEBomber>(pos1, spaceshipName, 1000.0f, pilot);
//            objects.push_back(std::move(bomber));

            } else if (type == "shuttle") {
//            auto shuttle = std::make_unique<Shuttle>(pos1, spaceshipName, 500.0f, pilot);
//            objects.push_back(std::move(shuttle));

            }
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

}

void Model::go() {

}

void Model::attack() {

}

void Model::shoot() {

}

void Model::stop() {

}

void Model::position() {

}

void Model::destination() {

}

void Model::exit() {

}
