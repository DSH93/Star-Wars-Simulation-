//
// Created by Dor Shukrun on 29/08/2024.
//

#include <fstream>
#include <sstream>
#include <algorithm>
#include "controller/Controller.h"



void Controller::processCommand() {
    while (!commands.empty()) {
        std::vector<std::string> command = commands.front();
        commands.pop();
        if (command[0] == "station" || command[0] == "fortress") {
            model.addSite(command);
        } else if (command[0] == "create") {
            model.create(command);
        } else if (command[0] == "status") {
            model.status();
        } else if (command[0] == "go") {
            model.go();
        } else if (command[0] == "attack") {
            model.attack();
        } else if (command[0] == "stop") {
            model.stop();


        } else if (command[0] == "show") {

        } else if (command[0] == "pan") {
            //
        } else if (command[0] == "zoom") {
            //
        } else if (command[0] == "default") {
                //
        } else if (command[0] == "exit") {
            model.exit();
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



std::vector<std::string> split(const std::string& line) {
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
        std::cout << "Enter command: ";
        std::getline(std::cin, line);
        if (line.empty()) continue;
        if (line == "exit") {
            model.exit();
            break;
        }
        std::vector<std::string> command = split(line);
        commands.push(command);
        processCommand();
    }
}