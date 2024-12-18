//
// Created by Dor Shukrun on 07/11/2024.
//

#ifndef STARWARSSIMULATION_MISSILE_H
#define STARWARSSIMULATION_MISSILE_H

#include "model/SpaceObject.h"
#include "model/spaceships/Spaceship.h"
#include <vector>

/**
 * @class Missile
 * @brief Represents a missile spaceship capable of targeting and destroying other objects.
 */
class Missile : public Spaceship {
private:
    Position target; ///< The target position of the missile.
    float distance; ///< Distance between the missile's origin and its target.
    bool isDestroyed = false; ///< Indicates whether the missile has been destroyed.

public:
    /**
     * @brief Constructor for the Missile class.
     *
     * @param destroyer Initial position of the missile's launch.
     * @param targetPos Position of the missile's target.
     * @param identifier Unique identifier for the missile.
     * @param sites List of space objects associated with the missile.
     */
    Missile(const Position &destroyer, const Position &targetPos, const std::string &identifier, const std::vector<std::shared_ptr<SpaceObject>>& sites);

    /**
     * @brief Displays the current status of the missile.
     *
     * Logs and outputs information such as position, target, and destruction state.
     */
    void status() override;

    /**
     * @brief Handles interaction with other space objects.
     *
     * @param other The space object to interact with.
     */
    void interact(std::shared_ptr<SpaceObject> other) override;

    /**
     * @brief Updates the missile's position and state during the simulation.
     */
    void update() override;

    /**
     * @brief Updates the missile and checks for collisions with Falcons.
     *
     * @param falconsPositions A list of Falcon positions to check against.
     * @return The identifier of the Falcon destroyed, if any.
     */
    std::string update(const std::vector<std::pair<std::string, Position>>& falconsPositions);

    /**
     * @brief Sets a new target for the missile.
     *
     * @param misTarget The new target position.
     */
    [[maybe_unused]] void setTarget(const Position &misTarget);

    /**
     * @brief Checks if the missile has been destroyed.
     *
     * @return True if the missile is destroyed, false otherwise.
     */
    [[nodiscard]] bool isMissileDestroyed() const;

    /**
     * @brief Gets the target position of the missile.
     *
     * @return The target position as a Position object.
     */
    [[nodiscard]] Position getTarget() const;

    /**
     * @brief Returns the type of the spaceship.
     *
     * @return The string "Missile".
     */
    std::string getType() const override { return "Missile"; }

    /**
     * @brief Destructor for the Missile class.
     */
    ~Missile() override = default;
};

#endif //STARWARSSIMULATION_MISSILE_H
