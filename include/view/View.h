//
// Created by Dor Shukrun on 29/08/2024.
//

#ifndef STARWARSSIMULATION_VIEW_H
#define STARWARSSIMULATION_VIEW_H

#include <vector>
#include <string>
#include "model/Position.h"

/**
 * @class View
 * @brief Manages the grid display and visualization for the simulation.
 */
class View {
private:
    int size; ///< Grid size (6 <= size <= 30).
    int scale; ///< Scale of the grid (1 <= scale <= 10).
    std::pair<int, int> origin; ///< Origin point of the grid.
    std::vector<std::vector<std::string>> grid; ///< Grid representation.
    std::vector<std::pair<std::string, Position>> positions; ///< List of positions to display.

    void updateGrid(); ///< Updates the grid with current positions.
    [[nodiscard]] bool isInGrid(int x, int y) const; ///< Checks if a position is within the grid bounds.

public:
    View(); ///< Default constructor initializing grid and parameters.

    /**
     * @brief Prints the current grid with positions.
     */
    void printGrid();

    /**
     * @brief Sets positions for objects to be rendered on the grid.
     * @param pos List of name and position pairs.
     */
    void setPositions(const std::vector<std::pair<std::string, Position>>& pos);

    /**
     * @brief Pans the grid view by adjusting the origin.
     * @param a Horizontal shift.
     * @param b Vertical shift.
     */
    void pan(int a, int b);

    /**
     * @brief Zooms the grid view by adjusting the scale.
     * @param s New scale value.
     */
    void zoom(int s);

    /**
     * @brief Sets the grid size.
     * @param dim New grid size value.
     */
    void setSize(int dim);

    /**
     * @brief Resets the view to default parameters.
     */
    void setDefault();
};

#endif //STARWARSSIMULATION_VIEW_H
