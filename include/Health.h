#pragma once

#include "gp/gp.h"
#include "Entity.h"

class Health : public Entity
{
    private:
        int         m_maxLife = 0;
        int         m_currentLife = 0;
        float       m_width = 30.f;
        float       m_height = 5.f;

    public:
        Health(int maxLife)
        : m_maxLife(maxLife), m_currentLife(maxLife)
        {}
        ~Health();

        int         getCurrentHealth() const;
        int         getMaxHealth() const;
        void        updateHealth(int healthChange);
        float       getBarWidth() const;
        float       getBarHeight() const;
};