#pragma once

#include "gp/gp.h"
#include "Entity.h"

class Grid : public Entity
{
    private:
        GPRect      m_gridBlock = { 0.f, 0.f, 0.f, 0.f };
        GPColor     m_color = { 0.f, 0.f, 0.f, 0.f };
        bool        m_empty = true;

    public:
        Grid();
        Grid(GPRect gridBlock, GPColor color);
        ~Grid();

        int             getGridStep();

        /**
        *   REVIEW:
        *   Devrait soit return const &, soit m_gridBlock et m_color en public.
        */
        GPRect&         getGridBlock();
        GPColor&        getColor();

        bool            isEmpty();

        void            changeGridState();

        void            draw(GPLib* gp);
};