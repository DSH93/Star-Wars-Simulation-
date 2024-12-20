//
// Created by Dor Shukrun on 24/08/2024.
//
#ifndef STARWARSSIMULATION_SHUTTLE_H
#define STARWARSSIMULATION_SHUTTLE_H

#include <memory>
#include <queue>
#include "Spaceship.h"
#include "model/agents/Midshipman.h"
#include "model/FortressStar.h"
#include "model/SpaceStation.h"

/**
 * @class Shuttle
 * @brief Represents a shuttle spaceship that can carry crystals and complete supply missions.
 */
class Shuttle : public Spaceship {
private:
    int crystalsContainers = 0; ///< Current number of crystal containers on the shuttle.
    int maxCrystalsContainers = SHUTTLE_MAX_CRYSTALS; ///< Maximum capacity for crystal containers.
    int powerUnits = SHUTTLE_INITIAL_POWER_UNITS; ///< Current defensive power units.
    int maxPowerUnits = SHUTTLE_MAX_POWER_UNITS; ///< Maximum defensive power units.
    Position fortress; ///< Position of the target fortress.
    Position station; ///< Position of the source station.
    std::shared_ptr<FortressStar> fortressStar; ///< Pointer to the target FortressStar.
    std::shared_ptr<SpaceStation> spaceStation; ///< Pointer to the source SpaceStation.
    std::queue<std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>>> supplyMissions; ///< Queue of supply missions (source and target).
    std::shared_ptr<Midshipman> pilot; ///< Pointer to the Midshipman piloting the shuttle.
    bool finishedMission = true; ///< Flag indicating whether the shuttle has completed its current mission.
    bool needToWait = false; ///< Flag indicating if the shuttle needs to wait at a station.

public:
    /**
     * @brief Constructor for the Shuttle class.
     *
     * @param pos1 Initial position of the shuttle.
     * @param identifier1 Identifier for the shuttle.
     * @param speed Speed of the shuttle.
     * @param pilot Pilot of the shuttle.
     * @param sites List of space objects associated with the shuttle.
     *
     * @throws std::invalid_argument if the pilot is null.
     */
    Shuttle(const Position &pos1, const std::string& identifier1, float speed, const std::shared_ptr<Midshipman>& pilot, const std::vector<std::shared_ptr<SpaceObject>>& sites);

    /**
     * @brief Updates the shuttle's state during the simulation.
     *
     * This function manages power, progress on supply missions, and position updates.
     */
    void update() override;

    /**
     * @brief Interacts with another space object.
     *
     * @param other The other space object to interact with.
     */
    void interact(std::shared_ptr<SpaceObject> other) override;

    /**
     * @brief Loads crystals from a specified space station.
     *
     * @param st A shared pointer to the SpaceStation to load crystals from.
     */
    void loadCrystals(const std::shared_ptr<SpaceStation> &st);

    /**
     * @brief Starts the current supply mission by initiating movement to the target fortress.
     */
    void startSupplyMission();

    /**
     * @brief Completes the current supply mission and unloads crystals at the fortress.
     */
    void finishSupplyMission();

    /**
     * @brief Decreases the defensive power units of the shuttle.
     *
     * If power units reach zero, the shuttle's state is updated to DEAD.
     */
    void decreaseDefPowerUnits();

    /**
     * @brief Gets the current defensive power units of the shuttle.
     *
     * @return Current power units as an integer.
     */
    [[nodiscard]] int getDefPowerUnits() const;

    /**
     * @brief Unloads all crystals currently on the shuttle.
     */
    void unloadCrystals();

    /**
     * @brief Adds a supply mission to the shuttle's mission queue.
     *
     * @param mission A pair containing a source SpaceStation and a target FortressStar.
     */
    void addSupplyMission(const std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>>& mission);

    /**
     * @brief Returns the type of the spaceship.
     *
     * @return The string "Shuttle".
     */
    std::string getType() const override { return "Shuttle"; }

    /**
     * @brief Prints the current status of the shuttle.
     *
     * This includes information about crystals, power units, and mission state.
     */
    void status() override;
};

#endif //STARWARSSIMULATION_SHUTTLE_H
