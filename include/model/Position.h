#ifndef STARWARSSIMULATION_POSITION_H
#define STARWARSSIMULATION_POSITION_H

#include <cmath>
#include <iostream>
#include <string>

/**
 * @class Position
 * @brief Represents a position in a 2D coordinate system.
 *
 * The Position class manages (x, y) coordinates and provides utility methods
 * for movement, distance calculations, and formatting.
 */
class Position {
private:
    float x; ///< The x-coordinate of the position.
    float y; ///< The y-coordinate of the position.
    static constexpr float UNIT_TO_KM = 1000.0f; ///< Conversion factor from unit to kilometers.

public:
    /**
     * @brief Constructor for Position.
     *
     * @param x Initial x-coordinate. Default is 0.0f.
     * @param y Initial y-coordinate. Default is 0.0f.
     */
    explicit Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    /**
     * @brief Copy constructor.
     *
     * @param Other The Position object to copy from.
     */
    Position(Position const &Other) = default;

    /**
     * @brief Move constructor.
     *
     * @param other The Position object to move from.
     */
    Position(Position&& other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     *
     * @param other The Position object to copy from.
     * @return Reference to the current object.
     */
    Position& operator=(const Position& other) = default;

    /**
     * @brief Move assignment operator.
     *
     * @param other The Position object to move from.
     * @return Reference to the current object.
     */
    Position& operator=(Position&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Position() = default;

    /**
     * @brief Gets the x-coordinate.
     *
     * @return The x-coordinate as a float.
     */
    [[nodiscard]] float getX() const { return x; }

    /**
     * @brief Gets the y-coordinate.
     *
     * @return The y-coordinate as a float.
     */
    [[nodiscard]] float getY() const { return y; }

    /**
     * @brief Sets the x-coordinate.
     *
     * @param x1 New x-coordinate value.
     */
    void setX(float x1) { this->x = x1; }

    /**
     * @brief Sets the y-coordinate.
     *
     * @param y1 New y-coordinate value.
     */
    void setY(float y1) { this->y = y1; }

    /**
     * @brief Moves the position to new (x, y) coordinates.
     *
     * @param x1 New x-coordinate.
     * @param y1 New y-coordinate.
     */
    void move(float x1, float y1) {
        setX(x1);
        setY(y1);
    }

    /**
     * @brief Calculates the distance between two positions.
     *
     * @param pos1 The first position.
     * @param pos2 The second position.
     * @return The distance between the two positions in kilometers.
     */
    static float distance(const Position& pos1, const Position& pos2) {
        return pos1.distance(pos2.getX(), pos2.getY());
    }

    /**
     * @brief Calculates the distance to specific coordinates.
     *
     * @param x1 Target x-coordinate.
     * @param y1 Target y-coordinate.
     * @return The distance to the specified coordinates in kilometers.
     */
    [[nodiscard]] float distance(float x1, float y1) const {
        float a = this->x - x1;
        float b = this->y - y1;
        return std::sqrt(a * a + b * b) * UNIT_TO_KM;
    }

    /**
     * @brief Equality operator to compare positions.
     *
     * @param position The position to compare with.
     * @return True if both positions are equal, false otherwise.
     */
    bool operator==(const Position& position) const {
        return x == position.x && y == position.y;
    }

    /**
     * @brief Outputs the position to an ostream.
     *
     * @param os The output stream.
     * @param position The position to print.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Position &position) {
        os << "Position: (" << position.x << ", " << position.y << ")";
        return os;
    }

    /**
     * @brief Converts the position to a formatted string.
     *
     * @return A string representation of the position with up to 2 decimal places.
     */
    [[nodiscard]] std::string toString() const {
        auto formatNumber = [](float value) -> std::string {
            std::string str = std::to_string(value);
            size_t dotPos = str.find('.');
            if (dotPos != std::string::npos && dotPos + 3 < str.size()) {
                return str.substr(0, dotPos + 3);
            }
            return str;
        };

        return "(" + formatNumber(x) + ", " + formatNumber(y) + ")";
    }
};

namespace std {
    /**
     * @brief Hash function specialization for Position.
     */
    template<>
    struct hash<Position> {
        size_t operator()(const Position& pos) const {
            return hash<float>()(pos.getX()) ^ (hash<float>()(pos.getY()) << 1);
        }
    };
}

#endif // STARWARSSIMULATION_POSITION_H
