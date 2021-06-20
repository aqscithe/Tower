#pragma once

#include <string>

#include "gp/gp.h"
#include "Vector2.h"

class Entity
{
    protected:
        static unsigned int m_entityCount;
        std::string         m_name;
        Vector2             m_position = {0.f, 0.f};
        GPColor             m_fill = { 0.f, 0.f, 0.f, 0.f };

    public:
        Entity();

        ~Entity();

        void            draw(GPLib* gp);

        static void     increaseEntities();

        virtual void    updatePosition(float x, float y);
        Vector2         getPosition();
};