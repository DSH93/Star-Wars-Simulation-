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
    for (auto &object : objects) {
        object->update();
    }

}

int Model::getCurrentTime() {
    return Timer::getCurrentTick();
}
#include <algorithm>
#include <random>


