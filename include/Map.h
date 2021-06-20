#pragma once

#include <vector>
#include <string>

#include "gp/gp.h"
#include "Grid.h"
#include "StandardTower.h"
#include "World.h"

class Grid;
class Map
{
    private:
        int                 m_gridCount = 0;
        std::vector<Grid*>  m_gridBlocked;
        std::vector<Grid*>  m_gridPath;
        std::vector<Grid*>  m_gridTower;
        int                 m_startIndex = 0;
        int                 m_endIndex = 0;

    public:
        Map();
        ~Map();

        /** REVIEW: Utilise const GPRect& et const GPColor& pour eviter des copies. */
        void            addGrid(int index, GPRect gridBlock, GPColor color);

        /** REVIEW: Utilise ta class Vector2 */
        void            findGrid(GPVector2 m_position, World&);

        Grid*           getTowerGridElement(GPVector2 position) const;
        Grid*           getPathGridElement(GPVector2 position) const;

        void            draw(GPLib* gp);


};