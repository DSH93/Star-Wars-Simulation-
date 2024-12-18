//
// Created by Dor Shukrun on 29/08/2024.
//

#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>
#include "controller/Controller.h"
#include "model/Timer.h"
#include "ModelTester.h"


void Controller::processCommand() {
    while (!commands.empty()) {
        std::vector<std::string> command = commands.front();
        std::vector<std::pair<std::string, Position>> positions = model.getPositions();
        view->setPositions(positions);
        commands.pop();

        CommandID cmdID = CMD_UNKNOWN;


        if (commandMap.find(command[0]) != commandMap.end()) {
            cmdID = commandMap.at(command[0]);
        } else if (command.size() > 1 && commandMap.find(command[1]) != commandMap.end()) {
            cmdID = commandMap.at(command[1]);
        }

        switch (cmdID) {
            case CMD_STATION:
            case CMD_FORTRESS:
                Logger::getInstance().log("COMMAND: Adding site: " + command[1]);
                model.addSite(command);
                break;

            case CMD_CREATE:
                Logger::getInstance().log("COMMAND: Creating object: " + command[1]);
                model.create(command);
                break;

            case CMD_STATUS:
                Logger::getInstance().log("COMMAND: Status");
                if (command.size() == 1) {
                    model.statusCMD();
                } else {
                    model.statusByObj(command);
                }
                break;

            case CMD_GO:
                model.goCMD();
                break;

            case CMD_SHOW:
                Logger::getInstance().log("VIEW COMMAND");
                view->printGrid();
                break;

            case CMD_PAN:
                Logger::getInstance().log("VIEW COMMAND");
                view->pan(std::stoi(command[1]), std::stoi(command[2]));
                break;

            case CMD_ZOOM:
                Logger::getInstance().log("VIEW COMMAND");
                view->zoom(std::stoi(command[1]));
                break;

            case CMD_SIZE:
                Logger::getInstance().log("VIEW COMMAND");
                view->setSize(std::stoi(command[1]));
                break;

            case CMD_ATTACK:
                Logger::getInstance().log("COMMAND: Attack");
                model.attackCMD(command);
                break;

            case CMD_STOP:
                Logger::getInstance().log("COMMAND: Stop");
                model.stopCMD(command);
                break;

            case CMD_SHOOT:
                Logger::getInstance().log("COMMAND: Shoot");
                model.shootCMD(command);
                break;

            case CMD_POSITION:
                Logger::getInstance().log("COMMAND: Position");
                model.positionCMD(command);
                break;

            case CMD_DESTINATION:
                Logger::getInstance().log("COMMAND: Destination");
                model.destinationCMD(command);
                break;

            case CMD_COURSE:
                Logger::getInstance().log("COMMAND: Course");
                model.courseCMD(command);
                break;

            case CMD_START_SUPPLY:
                Logger::getInstance().log("COMMAND: Start Supply");
                model.SupplyCMD(command);
                break;

            case CMD_TEST: {
                ModelTester tester = ModelTester();
                tester.runAllTests();
                break;
            }
            case CMD_PLAY:
                progressTimeInteractive(std::stoi(command[1]));
                break;

            case CMD_DEFAULT:
                view->setDefault();
                break;


            default:
                std::cerr << "Unknown command: " << command[0] << std::endl;
                break;
        }
    }
}

void clearScreen() {
    for (int j = 0; j < 16; ++j) {
        std::cout << "\n";
    }
    std::cout << std::flush;
}

void Controller::progressTimeInteractive(int timeUnits) {
    for (int i = 0; i < timeUnits; i++) {
        clearScreen();
        view->printGrid();
        model.goCMD();
        std::vector<std::pair<std::string, Position>> positions = model.getPositions();

        view->setPositions(positions);
        // Clear the screen before printing the updated grid
        std::this_thread::sleep_for(std::chrono::seconds (1));

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
    Logger::getInstance().log("Loading sites from " + std::string(argv[1]));
    if (!file) {
        Logger::getInstance().log(ERROR_FILE_NOT_FOUND + std::string(argv[1]), Logger::Level::ERROR);
        throw std::runtime_error(ERROR_FILE_NOT_FOUND + std::string(argv[1]));
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
    Logger::getInstance().log("Simulation started");
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

        if (line == COMMAND_EXIT) {
            break;
        }

        std::vector<std::string> command = split(line);
        commands.push(command);
        processCommand();

        std::cout.flush();
    }
}

