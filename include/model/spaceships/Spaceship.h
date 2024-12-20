#ifndef STARWARSSIMULATION_SPACESHIP_H
#define STARWARSSIMULATION_SPACESHIP_H

#include <map>
#include <queue>
#include <unordered_map>
#include "model/SpaceObject.h"

/**
 * @class Spaceship
 * @brief Abstract base class for all types of spaceships.
 */
class Spaceship : public SpaceObject {
public:
    /**
     * @enum SpaceshipState
     * @brief Represents the possible states of a spaceship.
     */
    enum class SpaceshipState {
        STOPPED, ///< Spaceship is stopped.
        DOCKED,  ///< Spaceship is docked at a station.
        MOVING,  ///< Spaceship is in motion.
        DEAD     ///< Spaceship is destroyed.
    };

    /**
     * @enum flightMethod
     * @brief Represents the flight method of the spaceship.
     */
    enum class flightMethod {
        COURSE,       ///< Movement by course (angle).
        DESTINATION,  ///< Movement towards a specific destination.
        POS           ///< Movement to a specific position.
    };

protected:
    SpaceshipState state; ///< Current state of the spaceship.
    flightMethod method; ///< Current flight method used.
    Position destination; ///< Current destination of the spaceship.
    [[maybe_unused]] Direction direction; ///< Direction of movement.
    float speed; ///< Speed of the spaceship in units per hour.
    std::vector<std::shared_ptr<SpaceObject>> sites; ///< List of nearby space objects.
    std::unordered_map<Position, std::shared_ptr<SpaceObject>> sitesMap; ///< Map of sites by position.
    std::unordered_map<std::string, Position> sitesDestinations; ///< Map of site destinations by ID.

    /**
     * @brief Logs the creation of a spaceship.
     * @param spaceshipType Type of the spaceship.
     * @param identifier Unique identifier of the spaceship.
     * @param speed Speed of the spaceship.
     */
    static void logCreation(const std::string& spaceshipType, const std::string& identifier, float speed);

public:
    /**
     * @brief Constructor for the Spaceship class.
     * @param pos Initial position of the spaceship.
     * @param identifier Unique identifier of the spaceship.
     * @param sites List of nearby space objects for reference.
     */
    Spaceship(const Position& pos, const std::string& identifier, const std::vector<std::shared_ptr<SpaceObject>>& sites);

    /**
     * @brief Sets the speed of the spaceship.
     * @param newSpeed New speed value.
     */
    void setSpeed(float newSpeed) { this->speed = newSpeed; }

    /**
     * @brief Gets the current speed of the spaceship.
     * @return Speed as a float.
     */
    [[nodiscard]] float getSpeed() const { return speed; }

    /**
     * @brief Sets the state of the spaceship.
     * @param newState The new state to set.
     */
    void setState(SpaceshipState newState);

    /**
     * @brief Sets the destination by position.
     * @param dest Target position.
     */
    void setDestinationByPosition(const Position &dest);

    /**
     * @brief Gets the current position of the spaceship.
     * @return The updated position.
     */
    Position getCurrentPosition() override;

    /**
     * @brief Checks if the spaceship is still alive.
     * @return True if the spaceship is not dead.
     */
    [[nodiscard]] bool isAlive() const { return state != SpaceshipState::DEAD; }

    /**
     * @brief Moves the spaceship to a new position.
     * @param newPosition Target position.
     */
    virtual void move(const Position& newPosition);

    /**
     * @brief Stops the spaceship.
     */
    virtual void stop();

    /**
     * @brief Pure virtual function to handle interaction with other space objects.
     * @param other The space object to interact with.
     */
    void interact(std::shared_ptr<SpaceObject> other) override;

    /**
     * @brief Updates the state of the spaceship.
     */
    void update() override;

    /**
     * @brief Prints the status of the spaceship.
     */
    void status() override;

    /**
     * @brief Gets the type of the spaceship.
     * @return A string representing the spaceship type.
     */
    [[nodiscard]] std::string getType() const override = 0;

    /**
     * @brief Sets the course of the spaceship using an angle.
     * @param angle Direction angle in degrees.
     */
    void setCourse(float angle);

    /**
     * @brief Prints the current state of the spaceship.
     * @param typeName Name of the spaceship type.
     */
    void printState(const std::string &typeName);

    /**
     * @brief Prints the current flight method of the spaceship.
     * @param typeName Name of the spaceship type.
     */
    void printFlightMethod(const std::string &typeName);

    /**
     * @brief Sets the destination based on a site name.
     * @param siteName Name of the destination site.
     */
    void setSiteDestination(const std::string &siteName);

    /**
     * @brief Calculates the new position when flying on a course.
     * @return Updated position.
     */
    Position calculateCoursePosition();

    /**
     * @brief Calculates the new position when moving towards a destination.
     * @return Updated position.
     */
    Position calculateNewPosition();

    /**
     * @brief Gets the current state of the spaceship.
     * @return The state of the spaceship.
     */
    SpaceshipState getState();

    /**
     * @brief Virtual destructor for the Spaceship class.
     */
    ~Spaceship() override = default;
};

#endif //STARWARSSIMULATION_SPACESHIP_H
