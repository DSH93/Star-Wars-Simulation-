//
// Created by Dor Shukrun on 23/08/2024.
//

#include "model/Direction.h"

std::pair<float, float> Direction::getDirectionVector() {
    float x = cos(angle);
    float y = sin(angle);
    return std::make_pair(x, y);
}

Direction Direction::calculateDirection(const Position &src, const Position &dst) {
    float angle = calculateAngle(src, dst);
    return Direction(angle);

}

float Direction::calculateAngle(const Position &src, const Position &dst) {
    float x_values = dst.getX() - src.getX();
    float y_values = dst.getY() - src.getY();
    float angle = atan2(y_values, x_values);
    return angle;
}
