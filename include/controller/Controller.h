//
// Created by Dor Shukrun on 29/08/2024.
//

#ifndef STARWARSSIMULATION_CONTROLLER_H
#define STARWARSSIMULATION_CONTROLLER_H

#include <memory>
#include <queue>
#include "model/Model.h"
#include "view/View.h"
#include "Logger.h"

/**
 * @class Controller
 * @brief Manages the simulation flow by processing user commands and coordinating between the Model and View.
 */
class Controller {
private:
    std::shared_ptr<View> view; ///< Pointer to the View instance for rendering simulation states.
    Model& model; ///< Reference to the singleton instance of the Model class.
    std::queue<std::vector<std::string>> commands; ///< Queue of commands to be processed.

    /**
     * @enum CommandID
     * @brief Represents different types of commands that can be executed in the simulation.
     */
    enum CommandID {
        CMD_STATION,
        CMD_FORTRESS,
        CMD_CREATE,
        CMD_STATUS,
        CMD_GO,
        CMD_SHOW,
        CMD_PAN,
        CMD_ZOOM,
        CMD_SIZE,
        CMD_ATTACK,
        CMD_STOP,
        CMD_SHOOT,
        CMD_POSITION,
        CMD_COURSE,
        CMD_START_SUPPLY,
        CMD_TEST,
        CMD_PLAY,
        CMD_DEFAULT,
        CMD_DESTINATION,
        CMD_UNKNOWN
    };

    /**
     * @brief Map linking command strings to their corresponding CommandID.
     */
    const std::unordered_map<std::string, CommandID> commandMap = {
            {COMMAND_STATION, CMD_STATION},
            {COMMAND_FORTRESS, CMD_FORTRESS},
            {COMMAND_CREATE, CMD_CREATE},
            {COMMAND_STATUS, CMD_STATUS},
            {COMMAND_GO, CMD_GO},
            {COMMAND_SHOW, CMD_SHOW},
            {COMMAND_PAN, CMD_PAN},
            {COMMAND_ZOOM, CMD_ZOOM},
            {COMMAND_SIZE, CMD_SIZE},
            {COMMAND_ATTACK, CMD_ATTACK},
            {COMMAND_STOP, CMD_STOP},
            {COMMAND_SHOOT, CMD_SHOOT},
            {COMMAND_POSITION, CMD_POSITION},
            {COMMAND_COURSE, CMD_COURSE},
            {COMMAND_START_SUPPLY, CMD_START_SUPPLY},
            {COMMAND_TEST, CMD_TEST},
            {COMMAND_DEFAULT, CMD_DEFAULT},
            {COMMAND_DESTINATION, CMD_DESTINATION},
            {COMMAND_PLAY, CMD_PLAY}
    };

    /**
     * @brief Processes a single command from the queue.
     *
     * This method identifies the command type and calls the appropriate function in the Model or View.
     */
    void processCommand();


public:
    /**
     * @brief Constructs the Controller and initializes the View and Model.
     */
    Controller() : model(Model::getInstance()), view(std::make_shared<View>()) {}

    /**
     * @brief Starts the simulation by processing the input file and user commands.
     *
     * @param argc Number of command line arguments.
     * @param argv Array of command line arguments.
     */
    void run(int argc, char **argv);

    /**
     * @brief Loads and initializes sites from an input file.
     *
     * @param argv Array of command line arguments containing the input file path.
     */
    void loadAndInitializeSites(char **argv);

    /**
     * @brief Starts the simulation loop, waiting for user commands.
     *
     * Processes commands interactively until the exit command is received.
     */
    void startSimulation();

    /**
     * @brief Progresses the simulation interactively for a specified number of time units.
     *
     * Displays the updated simulation grid after each time step.
     * @param timeUnits The number of time units to progress.
     */
    void progressTimeInteractive(int timeUnits);
};

#endif //STARWARSSIMULATION_CONTROLLER_H
