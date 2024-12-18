//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_TIEBOMBER_H
#define STARWARSSIMULATION_TIEBOMBER_H

#include "Spaceship.h"
#include "model/agents/Commander.h"
#include "Missile.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "model/Position.h"

/**
 * @class TIEBomber
 * @brief Represents a TIE Bomber spaceship that autonomously visits the closest space sites in a routine.
 */
class TIEBomber : public Spaceship {
private:
    std::shared_ptr<Commander> pilot; ///< Pointer to the Commander piloting the TIE Bomber.
    std::unordered_set<std::shared_ptr<SpaceObject>> visitedSites; ///< Set of visited space sites for efficient lookup.
    std::shared_ptr<SpaceObject> closestSite; ///< Pointer to the closest space site.
    std::shared_ptr<SpaceObject> firstSite; ///< Pointer to the first site visited, used to restart the routine.

    /**
     * @brief Finds the closest space site that has not been visited yet.
     *
     * Updates the `closestSite` member variable with the closest unvisited site.
     */
    void findClosestSpaceSite();

    /**
     * @brief Resolves alphabetical order in case two sites are equidistant.
     *
     * @param site The new site being compared.
     * @return A shared pointer to the site that comes first alphabetically.
     */
    std::shared_ptr<SpaceObject> alpabeticalOrderCase(const std::shared_ptr<SpaceObject> &site);

    /**
     * @brief Moves the TIE Bomber to the closest unvisited space site.
     *
     * Resets the visited sites if all have been visited and restarts the routine.
     */
    void flyToClosestSpaceSite();

public:
    /**
     * @brief Constructor for the TIEBomber class.
     *
     * @param pos Initial position of the TIE Bomber.
     * @param identifier Unique identifier for the TIE Bomber.
     * @param speed Speed of the TIE Bomber (default: DEFAULT_TIE_BOMBER_SPEED).
     * @param pilot Shared pointer to the Commander piloting the TIE Bomber.
     * @param sites List of space objects for the TIE Bomber to visit.
     *
     * @throws std::invalid_argument if the pilot is null.
     */
    TIEBomber(const Position& pos, const std::string& identifier, float speed = DEFAULT_TIE_BOMBER_SPEED,
              const std::shared_ptr<Commander>& pilot = nullptr,
              const std::vector<std::shared_ptr<SpaceObject>>& sites = {});

    /**
     * @brief Updates the state of the TIE Bomber.
     *
     * Checks if the spaceship reached its destination and triggers interaction logic.
     */
    void update() override;

    /**
     * @brief Handles interaction with a space site.
     *
     * Marks the site as visited and moves to the next closest site.
     * @param other Shared pointer to the space object being interacted with.
     */
    void interact(std::shared_ptr<SpaceObject> other) override;

    /**
     * @brief Returns the type of the spaceship.
     *
     * @return The string "TIEBomber".
     */
    [[nodiscard]] std::string getType() const override { return "TIEBomber"; }
};

#endif //STARWARSSIMULATION_TIEBOMBER_H
