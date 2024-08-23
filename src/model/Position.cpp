//
// Created by Dor Shukrun on 23/08/2024.
//


#include <cmath>

#include "model/Position.h"


float Position::distance(Position position) const {
    return distance(position.x, position.y);
}

float Position::distance(float x1, float y1) const {
    float a = this->x - x1;
    float b = this->y - y1;
    return std::sqrt(a * a + b * b);
}

void Position::print() const {
    std::cout << "Position: (" << x << ", " << y << ")" << std::endl;

}

Position& Position::operator=(Position position) {
    if (this != &position) {
        x = position.x;
        y = position.y;
    }
    return *this;
}

bool Position::operator==(Position position) const {
    return x == position.x && y == position.y;
}


