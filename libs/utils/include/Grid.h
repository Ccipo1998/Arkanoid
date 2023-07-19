
#pragma once

#ifndef LIB
#define LIB __declspec(dllexport)
#endif // !LIB

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
    LIB Grid(float width, float height, unsigned int cellsNumberRow, unsigned int cellsNumberColumn, const vec2f& startingPosition);

    /*
    @brief
    Computed cell width getter
    */
    LIB float GetCellWidth();

    /*
    @brief
    Computed cell height getter
    */
    LIB float GetCellHeight();

    /*
    @brief
    Next free position getter
    */
    LIB vec2f GetNextFreePosition();

    /*
    @brief
    Random free position getter
    */
    LIB vec2f GetRandomFreePosition();

    LIB ~Grid();

private:

    float width;
    float height;
    float cellWidth;
    float cellHeight;
    unsigned int cellsNumberRow;
    unsigned int cellsNumberColumn;

    // TODO iterator instead indices?
    vec2f** grid;
    List<vec2ui*> freeCells;

};
