//
// Created by Dor Shukrun on 27/08/2024.
//

#ifndef STARWARSSIMULATION_FALCON_H
#define STARWARSSIMULATION_FALCON_H

#include <memory>
#include <vector>
#include "Spaceship.h"
#include "Shuttle.h"

/**
 * @class Falcon
 * @brief Represents a Falcon spaceship with attack capabilities.
 */
class Falcon : public Spaceship {
private:
    int attPowerUnits = FALCON_INITIAL_ATTACK_POWER; ///< Current attack power units of the Falcon.
    int maxAttPowerUnits = FALCON_MAX_ATTACK_POWER; ///< Maximum attack power units.

public:
    /**
     * @brief Constructor for the Falcon class.
     *
     * @param pos Initial position of the Falcon.
     * @param identifier Identifier for the Falcon.
     * @param patrolSites List of patrol sites the Falcon will interact with.
     */
    Falcon(Position& pos, const std::string& identifier, const std::vector<std::shared_ptr<SpaceObject>>& patrolSites = {});

    /**
     * @brief Interaction with another space object.
     *
     * Specifically checks for interaction with shuttles for attack behavior.
     *
     * @param other The space object to interact with.
     */
    void interact(std::shared_ptr<SpaceObject> other) override;

    /**
     * @brief Marks the Falcon as destroyed.
     *
     * Updates the spaceship state to DEAD.
     */
    void killFalcon();

    /**
     * @brief Retrieves the current attack power units.
     *
     * @return The current attack power units as an integer.
     */
    [[nodiscard]] int getAttPowerUnits() const;

    /**
     * @brief Increases the attack power units by one.
     */
    void increaseAttPowerUnits();

    /**
     * @brief Decreases the attack power units by one.
     */
    void decreaseAttPowerUnits();

    /**
     * @brief Checks whether the Falcon can attack a target.
     *
     * @param attackerPower The Falcon's attack power.
     * @param targetDefense The target's defensive power.
     * @param attackerPos The Falcon's position.
     * @param targetPos The target's position.
     * @param distanceToTarget Distance between the Falcon and the target.
     * @param closetBomber Distance to the closest bomber.
     *
     * @return True if the Falcon can attack; otherwise, false.
     */
    bool canAttack(int attackerPower, int targetDefense, const Position &targetPos, float distanceToTarget,
                   float closetBomber);

    /**
     * @brief Executes an attack on a specified target shuttle.
     *
     * @param target Shared pointer to the target Shuttle.
     * @param distanceToTarget Distance between the Falcon and the target.
     * @param closetBomber Distance to the closest bomber.
     */
    void attack(const std::shared_ptr<Shuttle>& target, float distanceToTarget, float closetBomber);

    /**
     * @brief Returns the type of the spaceship.
     *
     * @return The string "Falcon".
     */
    std::string getType() const override { return "Falcon"; }
};

#endif //STARWARSSIMULATION_FALCON_H
