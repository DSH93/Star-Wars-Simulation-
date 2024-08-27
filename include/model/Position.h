//
// Created by Dor Shukrun on 23/08/2024.
//
#ifndef STARWARSSIMULATION_POSITION_H
#define STARWARSSIMULATION_POSITION_H

#include <cmath>
#include <iostream>

class Position {
private:
    float x;
    float y;

public:
    Position(float x, float y) : x(x), y(y) {} // Constructor

    float getX() const { return x; }
    float getY() const { return y; }

    void setX(float x1) { this->x = x1; }
    void setY(float y1) { this->y = y1; }

    void move(float x1, float y1) {  // Move the position to the given x and y
        setX(x1);
        setY(y1);
    }

    void move(Position position) { // Move the position to the given position
        move(position.getX(), position.getY());
    }

    float distance(Position position) const { // Calculate the distance between the current position and the given position
        return distance(position.getX(), position.getY());
    }

    float distance(float x1, float y1) const { // Calculate the distance between the current position and the given x1 and y1
        float a = this->x - x1;
        float b = this->y - y1;
        return std::sqrt(a * a + b * b);
    }

    void print() const {
        std::cout << "Position: (" << x << ", " << y << ")" << std::endl;
    }

    Position& operator=(Position position) { // Assign the given position to the current position
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
};

#endif // STARWARSSIMULATION_POSITION_H
