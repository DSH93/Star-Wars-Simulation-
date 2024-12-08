//
// Created by Dor Shukrun on 29/08/2024.
//

#include <iomanip>
#include "view/View.h"

View::View(): size(25), scale(2), grid(size, std::vector<std::string>(size, ".")) {}
View::View(int size, int scale): size(size), scale(scale), grid(size, std::vector<std::string>(size, ".")) {}



void View::printGrid() {
    render();
    int gridSize = size;
    updateGrid();



    for (int row = (int(origin.first) + gridSize - 1); row >= int(origin.first); --row) {
        int scaledRow = row * scale;


        if (row % 3 == 0) {
            std::cout << std::setw(2) << scaledRow << "  ";
        } else {
            std::cout << "    ";
        }

        //
        for (const auto& cell : grid[row]) {
            std::cout << std::setw(2) << cell << "";
        }
        std::cout << std::endl;
    }


    std::cout << "    ";
    for (int col = int(origin.second); col <= int(origin.second) + gridSize; ++col) {
        if (col == 0) {
            std::cout << std::setw(2) << 0;

        } else if (col % 3 == 0) {
            std::cout << std::setw(2) << col * scale;
        } else  {
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
}

void View::setPositions(const std::vector<std::pair<std::string, Position>>& pos) {
    this->positions = pos;
}




void View::render() {
    std::cout << "Displaying positions in Euclidean space:\n";
    for (const auto &pos1: positions) {
        std::cout << pos1.first << " is at " << pos1.second.toString() << std::endl;
    }
}

void View::pan(float a, float b) {
    origin.first = a;
    origin.second = b;


}


void View::updateGrid(){
    pan(5.0,5.0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j] = ".";
        }
    }


    for (const auto& pos: positions) {
        std::string id = pos.first;
        id = id.substr(0, 2);
        Position pos1 = pos.second;
        int x = int(pos1.getX());
        int y = int(pos1.getY());

        x = int(x/scale);
        y = int(y/scale);

        if (x >= int(origin.first) && x < int(origin.first) + size && y >= int(origin.second) && y < int (origin.second) + size) {
            grid[y][x] = id;
        }
    }


}



