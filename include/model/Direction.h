#ifndef STARWARSSIMULATION_DIRECTION_H
#define STARWARSSIMULATION_DIRECTION_H

#include "Position.h"
#include <cmath>
#include <utility>

/**
 * @class Direction
 * @brief Represents a directional vector with an angle in degrees.
 *
 * The Direction class is used to calculate and manipulate directions between positions.
 */
class Direction {
private:
    float angle; ///< The angle in degrees representing the direction.

public:
    /**
     * @brief Constructs a Direction with a specific angle.
     *
     * @param angle1 The initial angle in degrees.
     */
    explicit Direction(float angle1) {
        angle = std::fmod(angle1, 360.0f);
    }

    /**
     * @brief Constructs a Direction from a source position to a destination position.
     *
     * @param src The source position.
     * @param dst The destination position.
     */
    Direction(Position src, Position dst) : angle(calculateAngle(src, dst)) {}

    /**
     * @brief Gets the angle of the direction in degrees.
     *
     * @return The angle in degrees.
     */
    [[nodiscard]] float getAngle() const {
        return angle;
    }

    /**
     * @brief Converts an angle in degrees to radians.
     *
     * @param degrees The angle in degrees.
     * @return The equivalent angle in radians.
     */
    static float degreesToRadians(float degrees) {
        return degrees * (float) M_PI / 180.0f;
    }

    /**
     * @brief Gets the angle in radians, adjusted by +90 degrees.
     *
     * @return The adjusted angle in radians.
     */
    [[nodiscard]] float getAngleInRadians() const {
        float fixedAngle = angle + 90.0f;
        return degreesToRadians(fixedAngle);
    }

    /**
     * @brief Sets a new angle for the direction.
     *
     * @param newAngle The new angle in degrees.
     */
    void setAngle(float newAngle) {
        angle = std::fmod(newAngle, 360.0f);
    }

    /**
     * @brief Calculates the angle between two positions.
     *
     * @param src The source position.
     * @param dst The destination position.
     * @return The angle in radians between the two positions.
     */
    static float calculateAngle(const Position &src, const Position &dst) {
        float x_values = dst.getX() - src.getX();
        float y_values = dst.getY() - src.getY();
        float angle1 = std::atan2(y_values, x_values);
        return angle1;
    }
};

#endif //STARWARSSIMULATION_DIRECTION_H
