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
#include "SpaceObject.h"
#include "Timer.h"


class Model {
private:
    std::vector<std::unique_ptr<SpaceObject>> objects;
    Model(); // provide Singleton

public:
    static Model& getInstance(); // provide the only instance of Model
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete; // prevent copy and assignment

    void addObject(std::unique_ptr<SpaceObject> object);
    void removeObject(const SpaceObject &object);

    static float calculateDistance(const Position& pos1, const Position& pos2);
    static Direction calculateDirection(const Position& from, const Position& to);

    void advanceTime();
    int getCurrentTime();

};


#endif //STARWARSSIMULATION_MODEL_H
