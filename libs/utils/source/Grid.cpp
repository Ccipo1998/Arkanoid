
#include "Grid.h"
#include "stdlib.h"
#include "time.h"

Grid::Grid(float width, float height, unsigned int cellsNumberRow, unsigned int cellsNumberColumn, const vec2f& startingPosition)
    : width(width)
    , height(height)
    , cellsNumberRow(cellsNumberRow)
    , cellsNumberColumn(cellsNumberColumn)
{
    // compute cell width and height
    this->cellWidth = float(width) / float(cellsNumberColumn);
    this->cellHeight = float(height) / float(cellsNumberRow);

    // allocate rows memory
    this->grid = new vec2f*[cellsNumberRow];

    // compute possible positions
    for (unsigned int i = 0; i < cellsNumberRow; ++i)
    {
        // allocate columns memory
        this->grid[i] = new vec2f[cellsNumberColumn];

        for (unsigned int j = 0; j < cellsNumberColumn; ++j)
        {
            this->grid[i][j] = vec2f(j * this->cellWidth + startingPosition.x, i * this->cellHeight + startingPosition.y);
            
            // add free cell
            this->freeCells.Add(new vec2ui(i, j));
        }
    }
}

float Grid::GetCellWidth()
{
    return this->cellWidth;
}

float Grid::GetCellHeight()
{
    return this->cellHeight;
}

vec2f Grid::GetNextFreePosition()
{
    /*
    if (this->freeCells.GetSize() == 0)
        return nullptr;
    */

    // get indices
    vec2ui ij = *this->freeCells[0];
    // remove free position
    this->freeCells.Remove(0);

    return this->grid[ij.x][ij.y];
}

vec2f Grid::GetRandomFreePosition()
{
    /*
    if (this->freeCells.GetSize() == 0)
        return nullptr;
    */

    // last element
    if (this->freeCells.GetSize() == 1)
    {
        // get indices
        vec2ui ij = *this->freeCells[0];
        // remove free position
        this->freeCells.Remove(0);
        
        return this->grid[ij.x][ij.y];
    }

    // get random index
    unsigned int index = rand() % (this->freeCells.GetSize() - 1);
    // get indices
    vec2ui ij = *this->freeCells[index];
    // remove free position
    this->freeCells.Remove(index);
    
    return this->grid[ij.x][ij.y];
}

Grid::~Grid()
{
    for (unsigned int i = 0; i < cellsNumberRow; ++i)
        delete[] this->grid[i];

    delete[] this->grid;
}
