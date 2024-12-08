//
// Created by Dor Shukrun on 29/08/2024.
//

#ifndef STARWARSSIMULATION_VIEW_H
#define STARWARSSIMULATION_VIEW_H

#include <vector>
#include <string>
#include "model/Position.h"

class View {
private:

    int size; // 6 <= size <= 30 (default 25)
    int scale; // 1 <= scale <= 10 (default 2)
    std::pair<float, float> origin = {0, 0};
    std::vector<std::vector<std::string>> grid;
    std::vector<std::pair<std::string, Position>> positions;

public:
    View();
    View(int size, int scale);


    void render(const std::vector<std::pair<std::string, Position>>& positions) ;

    ~View() = default;


    void printGrid();

    void updateGrid();

    void render();

    void setPositions(const std::vector<std::pair<std::string, Position>> &positions);

    void pan(float a, float b);
};

#endif //STARWARSSIMULATION_VIEW_H
