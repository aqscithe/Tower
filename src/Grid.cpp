#include "Grid.h"
#include "Vector2f.h"


Grid::Grid(GPRect gridBlock, GPColor color)
{
    this->m_gridBlock = gridBlock;
    this->m_color = color;
    Vector2f pos = { gridBlock.x, gridBlock.y };
    this->updatePosition(pos);
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
    /**
    *   REVIEW:
    *   Simplification:
    *   m_empty = !m_empty;
    */

    if (m_empty)
        m_empty = false;
    else
        m_empty = true;
}

void    Grid::draw(GPLib* gp)
{
}