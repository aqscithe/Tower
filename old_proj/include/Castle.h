#pragma once

#include "Resources.h"
#include "Entity.h"
#include "Vector2.h"

class Castle : public Entity
{
    private:
        int         m_health = 0;
        int         m_maxHealth = 0;
        GPRect      m_body = { 0.f, 0.f, 0.f, 0.f };

    public:
        Castle(int health)
        : m_health(health), m_maxHealth(health)
        {
            this->m_body.w = GridBlocks::gridStep / 2.f;
            this->m_body.h = GridBlocks::gridStep * 1.5f;
        }

        Castle(const Castle& castle)
        {
            this->m_health = castle.m_health;
        }

        ~Castle();

        int         getHealth() const;
        int         getMaxHealth() const;
        GPRect      getBody() const;

        void        updateHealth(int updatedHealth);

        void        setPosition(int endIndex);

        Castle&     operator=(const Castle& castle);
};