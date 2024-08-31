//
// Created by Dor Shukrun on 29/08/2024.
//

#ifndef STARWARSSIMULATION_CONTROLLER_H
#define STARWARSSIMULATION_CONTROLLER_H


#include <memory>
#include <queue>
#include "model/Model.h"
#include "view/View.h"

class Controller {
private:
    std::shared_ptr<View> view;
    int currentState = 0;
    Model& model;
    std::queue<std::vector<std::string>> commands;


public:
    Controller() : model(Model::getInstance()) {}

    void run(int argc, char **argv);

    void processCommand();

    void loadAndInitializeSites(char **argv);

    void startSimulation();





};


#endif //STARWARSSIMULATION_CONTROLLER_H
