#pragma once

#include <string>

#include "gp/gp.h"
#include "Vector2f.h"

class Entity
{
    protected:
        static unsigned int m_entityCount;
        std::string         m_name;
        Vector2f             m_position = {0.f, 0.f};
        GPColor             m_fill = { 0.f, 0.f, 0.f, 0.f };

    public:
        Entity();

        ~Entity();

        void            draw(GPLib* gp);

        /**
        *   REVIEW:
        *   Ne devrait pas exister. Le systeme m_entityCount devrait etre automatique. 
        */
        static void     increaseEntities();

        /**
        *   REVIEW:
        *   Utilise const Vector2f& en parametre.
        */
        virtual void    updatePosition(const Vector2f& vector);

        /**
        *   REVIEW:
        *   return const Vector2f& pour eviter une copie.
        */
        Vector2f         getPosition();
};