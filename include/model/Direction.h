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
    Direction(float angle) : angle(angle) {}
    Direction(Position src, Position dst) : angle(calculateAngle(src, dst)) {}

    float getAngle() const { return angle; }
    void setAngle(float angle) { Direction::angle = angle; }
    void rotate(float angle) { Direction::angle += angle; }

    std::pair<float, float> getDirectionVector() {
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
