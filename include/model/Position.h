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
    Position(float x, float y); // Constructor
    float getX() const { return x;}
    float getY() const { return y;}

    void setX(float x) { this->x = x;}
    void setY(float y) { this->y = y;}

    void move(float x, float y){  // Move the position to the given x and y
        setX(x);
        setY(y);
    }

    void move(Position position){ // Move the position to the given position
        move(position.getX(), position.getY());
    }

    float distance(Position position) const; // Calculate the distance between the current position and the given position
    float distance(float x1, float y1) const; // Calculate the distance between the current position and the given x1 and y1
    void print() const;

    Position& operator=(Position position); // Assign the given position to the current position
    bool operator==(Position position) const; // Check if the given position is equal to the current position

};


#endif //STARWARSSIMULATION_POSITION_H
