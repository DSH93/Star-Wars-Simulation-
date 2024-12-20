#ifndef STARWARSSIMULATION_STARDESTROYER_H
#define STARWARSSIMULATION_STARDESTROYER_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Spaceship.h"
#include "Missile.h"
#include "model/agents/Admiral.h"

/**
 * @class StarDestroyer
 * @brief Represents a Star Destroyer spaceship, capable of launching missiles.
 */
class StarDestroyer : public Spaceship {
private:
    std::shared_ptr<Admiral> pilot; ///< Pointer to the Admiral piloting the Star Destroyer.
    std::vector<std::string> destroyerMissiles; ///< List of active missile names.
    std::unordered_map<std::string, std::shared_ptr<Missile>> missilesMap; ///< Map of missile names to Missile objects.
    int missilesCounter = 0; ///< Counter to generate unique missile names.

    /**
     * @brief Creates a missile targeting a specific position.
     * @param targetPos Target position for the missile.
     * @return The name of the created missile.
     */
    std::string createMissile(Position targetPos);

public:
    /**
     * @brief Constructor for the StarDestroyer class.
     * @param pos Initial position of the Star Destroyer.
     * @param identifier Unique identifier for the Star Destroyer.
     * @param speed Speed of the Star Destroyer (default: DEFAULT_STAR_DESTROYER_SPEED).
     * @param pilot Shared pointer to the Admiral piloting the destroyer.
     * @param sites List of space objects for patrol reference.
     * @throws std::invalid_argument if the pilot is null.
     */
    StarDestroyer(const Position& pos, const std::string& identifier, float speed = DEFAULT_STAR_DESTROYER_SPEED,
                  const std::shared_ptr<Admiral>& pilot = nullptr, const std::vector<std::shared_ptr<SpaceObject>>& sites = {});

    /**
     * @brief Prints the status of the Star Destroyer and its active missiles.
     */
    void status() override;

    /**
     * @brief Updates all active missiles and checks for impacts with Falcons.
     * @param falconsPositions List of Falcon names and their positions.
     * @return Name of the Falcon destroyed, if any.
     */
    std::string missileUpdate(const std::vector<std::pair<std::string, Position>>& falconsPositions);

    /**
     * @brief Fires a missile towards a specified target position.
     * @param targetPos The target position for the missile.
     */
    void shoot(Position targetPos);

    /**
     * @brief Gets the names and positions of all active missiles.
     * @return A vector of pairs containing missile names and their current positions.
     */
    std::vector<std::pair<std::string, Position>> getMissilesNameAndPosition();

    /**
     * @brief Gets the type of the spaceship.
     * @return The string "Star Destroyer".
     */
    [[nodiscard]] std::string getType() const override { return "Star Destroyer"; }
};

#endif //STARWARSSIMULATION_STARDESTROYER_H
