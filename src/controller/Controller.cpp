//
// Created by Dor Shukrun on 29/08/2024.
//

#include <fstream>
#include <sstream>
#include <algorithm>
#include "controller/Controller.h"
#include "model/Timer.h"


void Controller::processCommand() {
    while (!commands.empty()) {
        std::vector<std::string> command = commands.front();
        std::vector<std::pair<std::string, Position>> positions = model.getPositions();
        view->setPositions(positions);
        commands.pop();
        if (command[0] == "station" || command[0] == "fortress") {
            model.addSite(command);
        } else if (command[0] == "create") {
            model.create(command);
        } else if (command[0] == "status") {
            if (command.size() == 1) {
                model.status();
            } else {
                model.statusByObj(command);
            }

        } else if (command[0] == "go") {
            model.go();
        } else if (command[0] == "show") {
            view->printGrid();

        } else if (command[0] == "pan") {
            view->pan(std::stoi(command[1]), std::stoi(command[2]));
        } else if (command[0] == "zoom") {
            view->zoom(std::stoi(command[1]));
        } else if (command[0] == "size") {
            view->setSize(std::stoi(command[1]));


        } else if (command[1] == "attack") {
            model.attack(command);
        } else if (command[1] == "stop") {
            model.stop(command);
        } else if (command[1] == "shoot") {
            model.shoot(command);
        } else if (command[1] == "fortress") {
            model.destination(command);
        } else if (command[1] == "position") {
            model.position(command);
        } else if (command[1] == "course") {
            model.course(command);

        } else if (command[1] == "start_supply") {
            model.addSupplyMission(command);
        }
    }
}


void Controller::run(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sites_file>" << std::endl;
        exit(1);
    }
    std::cout << "Welcome to Star Wars Simulation!" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    loadAndInitializeSites(argv);
    startSimulation();

}


std::vector<std::string> split(const std::string &line) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, ' ')) {
        std::stringstream sub_ss(token);
        std::string sub_token;
        while (std::getline(sub_ss, sub_token, ',')) {
            sub_token.erase(std::remove_if(sub_token.begin(), sub_token.end(), [](char c) {
                return c == '(' || c == ')' || c == '\r';
            }), sub_token.end());
            if (!sub_token.empty()) {
                tokens.push_back(sub_token);
            }
        }
    }
    return tokens;
}


void Controller::loadAndInitializeSites(char **argv) {
    std::ifstream file(argv[1]);
    std::cout << "Loading sites from " << argv[1] << std::endl;
    if (!file) {
        throw std::runtime_error("Error: file not found " + std::string(argv[1]));
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> commend = split(line);
        commands.push(commend);
    }

    file.close();
    if (!commands.empty()) processCommand();


}


void Controller::startSimulation() {
    std::string line;


    while (true) {
        std::cout << "Time " << Timer::getCurrentTick() << ": Enter command: " << std::endl;
        std::getline(std::cin, line);

        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            continue;
        }

        if (line == "exit") {
            break;
        }

        std::vector<std::string> command = split(line);
        commands.push(command);
        processCommand();

        std::cout.flush();
    }
}

