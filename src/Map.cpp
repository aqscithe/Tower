#include <iostream>

#include "Map.h"
#include "Resources.h"

Map::Map()
{}

Map::~Map()
{
    for (Grid* element : m_gridTower)
    {
        delete element;
    }
    for (Grid* element : m_gridBlocked)
    {
        delete element;
    }
    for (Grid* element : m_gridPath)
    {
        delete element;
    }
}

void    Map::addGrid(int index, GPRect gridBlock, GPColor color)
{
    if ((int)color.r)
        this->m_gridBlocked.push_back(new Grid(gridBlock, color));
    else if ((int)color.g)
        this->m_gridTower.push_back(new Grid(gridBlock, color));
    else if ((int)color.b)
        this->m_gridPath.push_back(new Grid(gridBlock, color));

    ++m_gridCount;
}

Grid* Map::getTowerGridElement(GPVector2 position) const
{
    for (Grid* element : m_gridTower)
    {
        if (Math::pointInsideRect(position, element->getGridBlock()))
            return element;
    }
    return nullptr;
}

Grid* Map::getPathGridElement(GPVector2 position) const
{
    for (Grid* element : m_gridPath)
    {
        if (Math::pointInsideRect(position, element->getGridBlock()))
            return element;
    }
    return nullptr;
}

/*
    Game::update
*/


void    Map::draw(GPLib* gp)
{
    int index = 0;

    for (auto i = m_gridBlocked.begin(); i != m_gridBlocked.end(); ++i)
    {
        // TODO: make a function for the pre drawing calculation
        // draw function uses x and y as the top left of the rect

        GPRect grid = m_gridBlocked.at(index)->getGridBlock();
        grid.x = grid.x + 0.5f * grid.w;
        grid.y = grid.y + 0.5f * grid.w;

        gpDrawRectFilled( gp, grid, m_gridBlocked.at(index)->getColor() );
        ++index;
    }

    index = 0;
    for (auto i = m_gridTower.begin(); i != m_gridTower.end(); ++i)
    {
        GPRect grid = m_gridTower.at(index)->getGridBlock();
        grid.x = grid.x + 0.5f * grid.w;
        grid.y = grid.y + 0.5f * grid.w;

        gpDrawRectFilled( gp, grid, m_gridTower.at(index)->getColor() );
        ++index;
    }

    index = 0;
    for (auto i = m_gridPath.begin(); i != m_gridPath.end(); ++i)
    {
        GPRect grid = m_gridPath.at(index)->getGridBlock();
        grid.x = grid.x + 0.5f * grid.w;
        grid.y = grid.y + 0.5f * grid.w;

        gpDrawRectFilled( gp, grid, m_gridPath.at(index)->getColor() );
        ++index;
    }
}