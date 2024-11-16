//
// Created by Dor Shukrun on 23/08/2024.
//
#ifndef STARWARSSIMULATION_POSITION_H
#define STARWARSSIMULATION_POSITION_H

#include <cmath>
#include <iostream>
#include <string>

class Position {
private:
    float x;
    float y;
    static constexpr float UNIT_TO_KM = 1000.0f; // Define unit-to-km conversion

public:
    Position(float x, float y) : x(x), y(y) {} // Constructor
    static float getUnitToKm() { return UNIT_TO_KM; }

    [[nodiscard]] float getX() const { return x; }

    [[nodiscard]] float getY() const { return y; }

    [[nodiscard]] float getXInKm() const { return x * UNIT_TO_KM; }

    [[nodiscard]] float getYInKm() const { return y * UNIT_TO_KM; }

    void setX(float x1) { this->x = x1; }

    void setY(float y1) { this->y = y1; }

    void move(float x1, float y1) { // Move the position to the given x and y
        setX(x1);
        setY(y1);
    }

    void move(Position position) { // Move the position to the given position
        move(position.getX(), position.getY());
    }

    [[nodiscard]] float distance(Position position) const { // Calculate distance to another position
        return distance(position.getX(), position.getY());
    }

    [[nodiscard]] float distance(float x1, float y1) const { // Calculate distance to specific coordinates
        float a = this->x - x1;
        float b = this->y - y1;
        return std::sqrt(a * a + b * b) * UNIT_TO_KM; // Convert to kilometers
    }


    void print() const {
        std::cout << "Position: (" << x << ", " << y << ")" << std::endl;
    }

    Position &operator=(Position position) { // Assign the given position to the current position
        if (this != &position) {
            x = position.x;
            y = position.y;
        }
        return *this;
    }

    bool operator==(Position position) const { // Check if the given position is equal to the current position
        return x == position.x && y == position.y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Position &position) { // Print the position
        os << "Position: (" << position.x << ", " << position.y << ")";
        return os;
    }

    [[nodiscard]] std::string toString() const {
        auto formatNumber = [](float value) -> std::string {
            std::string str = std::to_string(value);
            size_t dotPos = str.find('.');
            if (dotPos != std::string::npos && dotPos + 3 < str.size()) {
                return str.substr(0, dotPos + 3); // Keep up to 2 decimal places
            }
            return str; // Return as is if no need to trim
        };

        return "(" + formatNumber(x) + ", " + formatNumber(y) + ")";
    }

};

#endif // STARWARSSIMULATION_POSITION_H
