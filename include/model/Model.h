//
// Created by Dor Shukrun on 23/08/2024.
//

#ifndef STARWARSSIMULATION_MODEL_H
#define STARWARSSIMULATION_MODEL_H

#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include "Position.h"
#include "Direction.h"
#include "SpaceObject.h"
#include "Timer.h"
#include "model/SpaceStation.h"
#include "model/FortressStar.h"
#include "model/spaceships/Spaceship.h"
#include "model/spaceships/StarDestroyer.h"
#include "model/spaceships/TIEBomber.h"
#include "model/spaceships/Falcon.h"
#include "model/spaceships/Shuttle.h"
#include "model/spaceships/Missile.h"
#include "model/agents/ImperialAgent.h"
#include "model/agents/ConcreteImperialAgentFactory.h"
#include "model/agents/Commander.h"
#include "model/agents/Midshipman.h"
#include "model/agents/Admiral.h"

/**
 * @class Model
 * @brief Singleton class that manages the entire simulation, including objects, agents, and commands.
 */
class Model {
private:
    std::unordered_map<std::string, std::shared_ptr<SpaceObject>> objectsMap; ///< Map of space objects indexed by ID.
    std::unordered_map<std::string, std::shared_ptr<ImperialAgent>> agents; ///< Map of imperial agents indexed by name.
    std::vector<std::string> ids; ///< List of all object IDs.
    std::unordered_set <std::string> uniqueIds; ///< Set of unique object IDs.
    std::vector<std::string> starDestroyersSpaceships; ///< List of Star Destroyer IDs.
    std::vector<std::string> missiles; ///< List of active missile IDs.
    std::vector<std::string> falcons; ///< List of Falcon spaceship IDs.
    std::vector<std::string> sites; ///< List of site IDs (space stations and fortresses).
    unsigned int sitesNumber = 0; ///< Total number of sites.

    /**
     * @brief Private constructor to ensure Singleton pattern.
     */
    Model();

    /**
     * @brief Advances the simulation by one time step.
     */
    void advanceTime();

    /**
     * @brief Updates all Star Destroyers in the simulation.
     */
    void starDestroyerUpdate();

    /**
     * @brief Collects all patrol sites for spaceships.
     * @return Vector of shared pointers to SpaceObject representing patrol sites.
     */
    std::vector<std::shared_ptr<SpaceObject>> collectPatrolSites();

public:
    /**
     * @brief Retrieves the singleton instance of the Model.
     * @return Reference to the Model instance.
     */
    static Model &getInstance();

    Model(const Model &) = delete; ///< Delete copy constructor.
    Model &operator=(const Model &) = delete; ///< Delete copy assignment.

    /**
     * @brief Calculates the distance between two positions.
     * @param pos1 First position.
     * @param pos2 Second position.
     * @return Distance as a float.
     */
    static float calculateDistance(const Position &pos1, const Position &pos2);

    /**
     * @brief Adds a new site (Space Station or Fortress Star) to the simulation.
     * @param command Vector containing site details.
     */
    void addSite(const std::vector<std::string> &command);

    /**
     * @brief Creates troops or spaceships based on command input.
     * @param command Vector containing creation details.
     */
    void create(const std::vector<std::string> &command);

    /**
     * @brief Displays the status of all objects in the simulation.
     */
    void statusCMD();

    /**
     * @brief Continues the simulation by advancing one time step.
     */
    void goCMD();

    /**
     * @brief Handles an attack command from a Falcon spaceship.
     * @param command Vector containing attack details.
     */
    void attackCMD(const std::vector<std::string> &command);

    /**
     * @brief Handles a shoot command for Star Destroyers.
     * @param command Vector containing shooting details.
     */
    void shootCMD(const std::vector<std::string> &command);

    /**
     * @brief Stops a spaceship's movement and clears its missions.
     * @param command Vector containing stop command details.
     */
    void stopCMD(const std::vector<std::string> &command);

    /**
     * @brief Sets a spaceship's position to specified coordinates.
     * @param command Vector containing position details.
     */
    void positionCMD(const std::vector<std::string> &command);

    /**
     * @brief Sets a spaceship's destination to a specified site.
     * @param command Vector containing destination details.
     */
    void destinationCMD(const std::vector<std::string> &command);

    /**
     * @brief Sets the course for a spaceship.
     * @param command Vector containing course details.
     */
    void courseCMD(const std::vector<std::string> &command);

    /**
     * @brief Initializes the default site (Fortress Star).
     */
    void defaultSite();

    /**
     * @brief Initiates a supply mission for a shuttle.
     * @param command Vector containing supply mission details.
     */
    void SupplyCMD(const std::vector<std::string> &command);

    /**
     * @brief Displays the status of a specific object.
     * @param command Vector containing object details.
     */
    void statusByObj(const std::vector<std::string> &command);

    /**
     * @brief Validates whether an object exists.
     * @param objectName Name of the object.
     * @return True if the object exists, false otherwise.
     */
    bool validateObjectExists(const std::string &objectName);

    /**
     * @brief Validates whether an object exists with a specific role.
     * @param objectName Name of the object.
     * @param role Role of the object.
     * @return True if the object exists, false otherwise.
     */
    bool validateObjectExists(const std::string &objectName, const std::string &role);

    /**
     * @brief Finds the closest bomber to a given position.
     * @param attackerPos Position of the attacker.
     * @return Distance to the closest bomber.
     */
    float findClosetBomber(const Position &attackerPos);

    /**
     * @brief Retrieves the positions of all active objects in the simulation.
     * @return Vector of pairs containing object names and their positions.
     */
    std::vector<std::pair<std::string, Position>> getPositions() const;

    /**
     * @brief Creates a Falcon spaceship.
     * @param command Vector containing creation details.
     * @param name Name of the spaceship.
     * @param patrolSites Vector of patrol sites for the Falcon.
     */
    void createFalcon(const std::vector<std::string> &command, const std::string &name,
                      const std::vector<std::shared_ptr<SpaceObject>> &patrolSites);

    /**
     * @brief Creates a spaceship with a pilot (Destroyer, Bomber, Shuttle).
     * @param command Vector containing creation details.
     * @param type Type of the spaceship.
     * @param name Name of the spaceship.
     * @param patrolSites Vector of patrol sites.
     */
    void createSpaceshipWithPilot(const std::vector<std::string> &command, const std::string &type,
                                  const std::string &name, const std::vector<std::shared_ptr<SpaceObject>> &patrolSites);

    /**
     * @brief Creates a Star Destroyer spaceship.
     */
    void createDestroyer(const std::shared_ptr<ImperialAgent> &pilot, const Position &pos, const std::string &name,
                         const std::vector<std::shared_ptr<SpaceObject>> &patrolSites);

    /**
     * @brief Creates a TIE Bomber spaceship.
     */
    void createBomber(const std::shared_ptr<ImperialAgent> &pilot, const Position &pos, const std::string &name,
                      const std::vector<std::shared_ptr<SpaceObject>> &patrolSites);

    /**
     * @brief Creates a Shuttle spaceship.
     */
    void createShuttle(const std::shared_ptr<ImperialAgent> &pilot, const Position &pos, const std::string &name,
                       const std::vector<std::shared_ptr<SpaceObject>> &patrolSites);

    void createTroops(const std::vector<std::string> &command);

    void createSpaceship(const std::vector<std::string> &command);

    bool validateAndInsertId(const std::string &name);
};

#endif // STARWARSSIMULATION_MODEL_H
