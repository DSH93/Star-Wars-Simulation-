#ifndef STARWARSSIMULATION_SPACESTATION_H
#define STARWARSSIMULATION_SPACESTATION_H

#include <vector>
#include <memory>
#include "SpaceObject.h"

/**
 * @class SpaceStation
 * @brief Represents a space station that produces crystals and allows docking of shuttles.
 */
class SpaceStation : public SpaceObject {
private:
    int crystalsAmount; ///< Current amount of crystals in the space station.
    int productionRate; ///< Number of crystals produced per time unit.
    std::vector<std::shared_ptr<SpaceObject>> dockingShuttles; ///< List of shuttles docked at the space station.

public:
    /**
     * @brief Constructor for the SpaceStation class.
     *
     * @param crystalsAmount Initial number of crystals in the station.
     * @param productionRate Rate of crystal production per time unit.
     * @param position Position of the space station.
     * @param identifier Unique identifier for the space station.
     */
    SpaceStation(int crystalsAmount, int productionRate, Position position, const std::string& identifier);

    /**
     * @brief Displays the current status of the space station.
     *
     * Includes position, inventory, production rate, and details of any docked shuttles.
     */
    void status() override;

    /**
     * @brief Updates the state of the space station.
     *
     * Removes shuttles that are no longer at the station's position and increments crystal inventory.
     */
    void update() override;

    /**
     * @brief Returns the current position of the space station.
     *
     * @return Position object representing the space station's location.
     */
    Position getCurrentPosition() override;

    /**
     * @brief Unloads crystals from the space station.
     *
     * Unloads a fixed amount of crystals (up to 5) or all remaining crystals if less than 5.
     * @return The number of crystals unloaded.
     */
    int unloadCrystals();

    /**
     * @brief Handles interaction with another space object.
     *
     * Adds the interacting object to the list of docked shuttles.
     * @param other A shared pointer to the space object interacting with the station.
     */
    void interact(std::shared_ptr<SpaceObject> other) override;

    /**
     * @brief Returns the type of the space object.
     *
     * @return A string representing the type of the object: "SpaceStation".
     */
    [[nodiscard]] std::string getType() const override { return "SpaceStation"; }

    std::vector<std::shared_ptr<SpaceObject>> filterDockingShuttles();

    void printDockingShuttles();

};

#endif //STARWARSSIMULATION_SPACESTATION_H
