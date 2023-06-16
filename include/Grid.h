
#pragma once

#include "ArkanoidMath.h"
#include "ArkanoidList.hpp"

class Grid
{

public:

    /*
    @brief
    Constructor for a grid of cells
    @param width: maximum width of the grid
    @param height: maximum height of the grid
    @param cellsNumberRow: the number of cells in a row
    @paragraph cellsNumberColumn: the number of cells in a column
    */
    Grid(unsigned int width, unsigned int height, unsigned int cellsNumberRow, unsigned int cellsNumberColumn, const vec2f& startingPosition);

    /*
    @brief
    Computed cell width getter
    */
    float GetCellWidth();

    /*
    @brief
    Computed cell height getter
    */
    float GetCellHeight();

    /*
    @brief
    Next free position getter
    */
    vec2f GetNextFreePosition();

    /*
    @brief
    Random free position getter
    */
    vec2f GetRandomFreePosition();

    ~Grid();

private:

    unsigned int width;
    unsigned int height;
    float cellWidth;
    float cellHeight;
    unsigned int cellsNumberRow;
    unsigned int cellsNumberColumn;

    // TODO iterator instead indices?
    vec2f** grid;
    List<vec2ui*> freeCells;

};
