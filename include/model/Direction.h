//
// Created by Dor Shukrun on 23/08/2024.
//

#ifndef STARWARSSIMULATION_DIRECTION_H
#define STARWARSSIMULATION_DIRECTION_H

#include "Position.h"
#include <cmath>
#include <utility>

class Direction {
private:
    float angle;

public:
    explicit Direction(float angle) : angle(angle) {}

    Direction(Position src, Position dst) : angle(calculateAngle(src, dst)) {}

    [[nodiscard]] Position getCurrentPositionBySpeedAndTime(int speed, int time, Position pos) const {
        float x = pos.getXInKm() + float(speed) * float(time) * std::cos(angle);
        float y = pos.getYInKm() + float(speed) * float(time) * std::sin(angle);
        return {x / Position::getUnitToKm(), y / Position::getUnitToKm()}; // Convert back to internal units
    }

    [[nodiscard]] float getAngle() const {
        return angle;
    }

    void setAngle(float newAngle) { Direction::angle = newAngle; }

    void rotate(float newAngle) { Direction::angle += newAngle; }

    [[nodiscard]] std::pair<float, float> getDirectionVector() const {
        float x = std::cos(angle);
        float y = std::sin(angle);
        return std::make_pair(x, y);
    }

    static Direction calculateDirection(const Position &src, const Position &dst) {
        float angle = calculateAngle(src, dst);
        return Direction(angle);
    }

    static float calculateAngle(const Position &src, const Position &dst) {
        float x_values = dst.getX() - src.getX();
        float y_values = dst.getY() - src.getY();
        float angle = std::atan2(y_values, x_values);
        return angle;
    }
};

#endif //STARWARSSIMULATION_DIRECTION_H
