#ifndef STARWARSSIMULATION_FORTRESSSTAR_H
#define STARWARSSIMULATION_FORTRESSSTAR_H

#include <vector>
#include <memory>
#include <iostream>
#include "SpaceObject.h"

/**
 * @class FortressStar
 * @brief Represents a fortress that can store crystals and manage docking shuttles.
 *
 * The FortressStar class handles interactions with shuttles, updates its docking shuttles,
 * and manages its crystal inventory.
 */
class FortressStar : public SpaceObject {
private:
    int crystalAmount = 0; ///< The current amount of crystals stored in the fortress.
    std::vector<std::shared_ptr<SpaceObject>> dockingShuttles; ///< A list of shuttles currently docked at the fortress.

public:
    /**
     * @brief Constructor for the FortressStar class.
     *
     * @param crystalAmount The initial number of crystals in the fortress.
     * @param position The position of the fortress in the simulation.
     * @param identifier The unique identifier for the fortress.
     */
    FortressStar(int crystalAmount, Position position, const std::string& identifier)
            : SpaceObject(position, identifier), crystalAmount(crystalAmount) {}

    /**
     * @brief Displays the status of the fortress, including its position and crystal inventory.
     */
    void status() override {
        std::cout << "Fortress " << id << ", at Position: (" << position.getX() << ", " << position.getY()
                  << "), Inventory: " << crystalAmount << std::endl;
    }

    /**
     * @brief Handles interaction with another space object, such as docking a shuttle.
     *
     * @param other A shared pointer to the space object interacting with the fortress.
     */
    void interact(std::shared_ptr<SpaceObject> other) override {
        dockingShuttles.push_back(other);
    }

    /**
     * @brief Gets the current position of the fortress.
     *
     * @return The position of the fortress.
     */
    Position getCurrentPosition() override {
        return position; // Returns the current positionCMD of the fortress
    }

    /**
     * @brief Updates the fortress by filtering out shuttles no longer docked.
     */
    void update() override {
        if (!dockingShuttles.empty()) {
            std::vector<std::shared_ptr<SpaceObject>> updatedShuttles;
            for (const auto& shuttle : dockingShuttles) {
                if (shuttle->getCurrentPosition() == position) {
                    updatedShuttles.push_back(shuttle);
                }
            }
            dockingShuttles = std::move(updatedShuttles);
        }
    }

    /**
     * @brief Adds crystals to the fortress's inventory.
     *
     * @param amount The number of crystals to add.
     */
    void addCrystals(int amount) {
        crystalAmount += amount;
    }

    /**
     * @brief Returns the type of the space object.
     *
     * @return The string "FortressStar".
     */
    [[nodiscard]] std::string getType() const override {
        return "FortressStar";
    }
};

#endif //STARWARSSIMULATION_FORTRESSSTAR_H
