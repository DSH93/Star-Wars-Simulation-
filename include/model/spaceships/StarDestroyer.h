//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_STARDESTROYER_H
#define STARWARSSIMULATION_STARDESTROYER_H


#include <memory>
#include "Spaceship.h"
#include "model/agents/Admiral.h"
#include "Missile.h"
#include <unordered_map>
#include <vector>

class StarDestroyer : public Spaceship{
private:
    std::shared_ptr<Admiral> pilot;
    std::vector<std::string> destroyerMissiles;
    std::unordered_map<std::string, std::shared_ptr<Missile>> missilesMap{};
    int missilesCounter = 0;

public:
    StarDestroyer(Position& pos, const std::string& identifier, float speed = 2000.0f, const std::shared_ptr<Admiral>& pilot = nullptr)
            : Spaceship(pos, identifier), pilot(pilot) {
        if (!pilot) {
            throw std::invalid_argument("Pilot cannot be null");
        }
        std::cout << "Star Destroyer created" << std::endl;
    }


    void interact(std::shared_ptr<SpaceObject> other) override;
    void update() override;
    void status() override;
    std::string createMissile(Position targetPos);
    std::string missileUpdate(const std::vector<std::pair<std::string, Position>>& falconsPositions);
    void shoot(Position targetPos);
    std::vector<std::pair<std::string,Position>> getMissilesNameAndPosition();
    void clear() override;



};


#endif //STARWARSSIMULATION_STARDESTROYER_H
