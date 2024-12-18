//
// Created by Dor Shukrun on 29/08/2024.
//

#include <iomanip>
#include <iostream>
#include "view/View.h"
#include "Constant.h"

View::View() : size(DEFAULT_GRID_SIZE), scale(DEFAULT_SCALE), grid(MAX_GRID_SIZE,
  std::vector<std::string>(MAX_GRID_SIZE, EMPTY_CELL)), origin(DEFAULT_ORIGIN_X,DEFAULT_ORIGIN_Y) {}

void View::printGrid() {
    updateGrid();
    for (int gridRow = size - 1; gridRow >= 0; --gridRow) {
        int worldY = origin.second + gridRow;
        int scaledY = worldY * scale;

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
    int deltaX = a / scale;
    int deltaY = b / scale;

    origin.first += deltaX;
    origin.second += deltaY;
}

void View::updateGrid() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), EMPTY_CELL);
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
    if (s < MIN_SCALE || s > MAX_SCALE) {
        std::cerr << ERROR_INVALID_SCALE << std::endl;
        return;
    }
    this->scale = s;
}

void View::setSize(int dim) {
    if (dim < MIN_GRID_SIZE || dim > MAX_GRID_SIZE) {
        std::cerr << ERROR_INVALID_SIZE << std::endl;
        return;
    }
    this->size = dim;

}

void View::setDefault() {
    size = DEFAULT_GRID_SIZE;
    scale = DEFAULT_SCALE;
    origin = {DEFAULT_ORIGIN_X, DEFAULT_ORIGIN_Y};
    grid = std::vector<std::vector<std::string>>(30, std::vector<std::string>(30, "."));
    positions = std::vector<std::pair<std::string, Position>>();
}



