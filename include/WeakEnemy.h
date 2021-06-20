#pragma once

#include "gp/gp.h"
#include "Enemy.h"
#include "Vector2f.h"

class WeakEnemy : public Enemy
{
    private:

    public:
        WeakEnemy(Vector2f center)
        : Enemy(center)
        {
            this->m_name = "WeakEnemy";
            this->m_color = { 0.91f, 0.29f, 0.24f, 1.f };
            this->m_dmg = 20;
            this->m_dodgeChance = 5;
            this->m_position = { center.m_x, center.m_y };
            this->m_points = 50;
            this->m_money = 10;
            this->m_moveSpeed = 65.f;
            this->m_moveSpeedNormal = 80.f;
            this->m_health = new Health(20);
        }
        ~WeakEnemy();
};