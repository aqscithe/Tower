#pragma once

#include "gp/gp.h"
#include "Enemy.h"
#include "Vector2.h"

class HealingEnemy : public Enemy
{
    private:

    public:
        HealingEnemy(Vector2 center)
        : Enemy(center)
        {
            this->m_name = "HealingEnemy";
            this->m_radius = 8.f;
            this->m_color = { 0.6f, 0.53f, 0.37f, 1.f };
            this->m_dmg = 5;
            this->m_healValue = 3;
            this->m_healZone = 100.f;
            this->m_healFrequency = 10.f;
            this->m_healTimer = m_healFrequency;
            this->m_position = { center.getX(), center.getY() };
            this->m_points = 100;
            this->m_money = 25;
            this->m_moveSpeed = 65.f;
            this->m_moveSpeedNormal = 65.f;
            this->m_health = new Health(30);
        }
        ~HealingEnemy();
};