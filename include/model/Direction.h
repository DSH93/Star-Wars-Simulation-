//
// Created by Dor Shukrun on 23/08/2024.
//

#ifndef STARWARSSIMULATION_DIRECTION_H
#define STARWARSSIMULATION_DIRECTION_H


#include "Position.h"

class Direction {
private:
    float angle;

public:
    Direction(float angle) : angle(angle) {}
    float getAngle() const {return angle;}
    void setAngle(float angle) {Direction::angle = angle;}
    void rotate(float angle) {Direction::angle += angle;}

    std::pair<float, float> getDirectionVector();
    Direction calculateDirection(const Position &src, const Position &dst);
    float calculateAngle(const Position &src, const Position &dst);


};


#endif //STARWARSSIMULATION_DIRECTION_H
