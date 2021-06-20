#include "Grid.h"


// Grid::Grid()
// {}

Grid::Grid(GPRect gridBlock, GPColor color)
{
    this->m_gridBlock = gridBlock;
    this->m_color = color;
    this->updatePosition(gridBlock.x, gridBlock.y);
}

Grid::~Grid()
{}

GPRect&      Grid::getGridBlock()
{
    return m_gridBlock;
}

GPColor&     Grid::getColor()
{
    return m_color;
}

bool        Grid::isEmpty()
{
    return m_empty;
}

void        Grid::changeGridState()
{
    if (m_empty)
        m_empty = false;
    else
        m_empty = true;
}

void    Grid::draw(GPLib* gp)
{
}