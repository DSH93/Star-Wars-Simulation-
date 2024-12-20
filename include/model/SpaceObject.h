#ifndef STARWARSSIMULATION_SPACEOBJECT_H
#define STARWARSSIMULATION_SPACEOBJECT_H

#include "Position.h"
#include "Direction.h"
#include <string>
#include <utility>
#include <stdexcept> // For std::invalid_argument
#include <memory>
#include "Timer.h"

/**
 * @class SpaceObject
 * @brief Abstract base class representing a generic space object.
 *
 * This class serves as a base for various space objects in the simulation.
 * It provides common properties such as position, ID, and methods for interaction and status updates.
 */
class SpaceObject : public std::enable_shared_from_this<SpaceObject> {
protected:
    Position position; ///< Current position of the space object.
    std::string id; ///< Unique identifier for the space object.
    int currentTime; ///< Current simulation time for the object.

public:
    /**
     * @brief Constructor for SpaceObject.
     *
     * @param pos Initial position of the space object.
     * @param identifier Unique identifier for the space object.
     */
    SpaceObject(const Position& pos, const std::string& identifier)
            : position(pos), id(validateId(identifier)), currentTime(Timer::getCurrentTick()) {}

    /**
     * @brief Gets the current position of the space object.
     *
     * @return The position as a Position object.
     */
    [[nodiscard]] Position getPosition() const { return position; }

    /**
     * @brief Gets the ID of the space object.
     *
     * @return The ID as a string.
     */
    [[nodiscard]] std::string getId() const { return id; }

    /**
     * @brief Pure virtual function to display the status of the space object.
     */
    virtual void status() = 0;

    /**
     * @brief Pure virtual function for interaction with another space object.
     *
     * @param other A shared pointer to the other space object.
     */
    virtual void interact(std::shared_ptr<SpaceObject> other) = 0;

    /**
     * @brief Pure virtual function to get the current position of the space object.
     *
     * @return The current position as a Position object.
     */
    virtual Position getCurrentPosition() = 0;

    /**
     * @brief Destructor.
     */
    virtual ~SpaceObject() = default;

    /**
     * @brief Pure virtual function to update the state of the space object.
     */
    virtual void update() = 0;

    /**
     * @brief Advances the simulation time for the space object.
     */
    void advanceTime() { currentTime++; }

    /**
     * @brief Gets the type of the space object.
     *
     * @return The type as a string.
     */
    [[nodiscard]] virtual std::string getType() const = 0;

private:
    /**
     * @brief Validates the ID of the space object.
     *
     * Ensures that the ID does not exceed the maximum length.
     *
     * @param identifier The ID to validate.
     * @return The validated ID.
     *
     * @throws std::invalid_argument If the ID exceeds the maximum length.
     */
    static std::string validateId(const std::string& identifier) {
        if (identifier.length() > MAX_ID_LENGTH) { // indexing starts from 0
            throw std::invalid_argument("ID must be less than " + std::to_string(MAX_ID_LENGTH) + " characters.");
        }
        return identifier;
    }
};

#endif //STARWARSSIMULATION_SPACEOBJECT_H
