//
// Created by Dor Shukrun on 29/08/2024.
//

#include <iomanip>
#include <iostream>
#include "view/View.h"

View::View() : size(25), scale(2), grid(30, std::vector<std::string>(30, ".")), origin(0,0) {}

void View::printGrid() {
    updateGrid();


    for (int gridRow = size - 1; gridRow >= 0; --gridRow) {
        int worldY = origin.second + gridRow;
        int scaledY = worldY * scale;

        // 25 + 0 = 25 default situation
        // 25 * 2 = 50

        // 20 + 25 = 45 pan 20 20
        // 45 * 2 = 90

        if (worldY % 3 == 0) {
            std::cout << std::setw(3) << scaledY << "  ";
        } else {
            std::cout << "     ";
        }



        for (int gridCol = 0; gridCol < size; ++gridCol) {
            std::cout << std::setw(2) << grid[gridRow][gridCol];
        }
        std::cout << "\n";
    }


    std::cout << "     ";
    for (int gridCol = 0; gridCol < size; ++gridCol) {
        int worldX = origin.first + gridCol;
        int scaledX = worldX * scale;

        if (worldX == 0) {
            std::cout << std::setw(2) << 0;
        } else if (worldX % 3 == 0) {
            std::cout << std::setw(2) << scaledX;
        } else {
            std::cout << "  ";
        }
    }
    std::cout << "\n";
}

void View::setPositions(const std::vector<std::pair<std::string, Position>>& pos) {
    this->positions = pos;
}


void View::pan(int a, int b) {
    // הפיכת ההזזה מיחידות עולם (a,b) ליחידות גריד
    int deltaX = a / scale;
    int deltaY = b / scale;

    origin.first += deltaX;
    origin.second += deltaY;
}

void View::updateGrid() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), ".");
    }

    for (const auto& posPair : positions) {
        const std::string& name = posPair.first;
        const Position& pos = posPair.second;

        std::string id = name.substr(0, 2);


        int x = (int) pos.getX() /(int) scale;
        int y = (int) pos.getY() /(int) scale;

        if (isInGrid(x, y)) {
            int gridX = x - origin.first;
            int gridY = y - origin.second;

            grid[gridY][gridX] = id;
        }
    }
}

bool View::isInGrid(int x, int y) const {
    return x >= origin.first && x < origin.first + size &&
           y >= origin.second && y < origin.second + size;
}

void View::zoom(int s) {
    if (s < 1 || s > 10) {
        std::cerr << "Error: Invalid scale" << std::endl;
        return;
    }
    this->scale = s;
}

void View::setSize(int dim) {
    if (dim < 6 || dim > 30) {
        std::cerr << "Error: Invalid size" << std::endl;
        return;
    }
    this->size = dim;

}

void View::setDefault() {
    size = 25;
    scale = 2;
    origin = {0, 0};
    grid = std::vector<std::vector<std::string>>(30, std::vector<std::string>(30, "."));
    positions = std::vector<std::pair<std::string, Position>>();
}