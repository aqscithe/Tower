#pragma once

#include "gp/gp.h"
#include "Enemy.h"
#include "Vector2f.h"

class StrongEnemy : public Enemy
{
    private:

    public:
        StrongEnemy(Vector2f center)
        : Enemy(center)
        {
            this->m_name = "StrongEnemy";
            this->m_radius = 15.f;
            this->m_color = { 0.93f, 1.f, 0.f, 1.f };
            this->m_dmg = 40;
            this->m_dmgReduction = 0.05f;
            this->m_position = { center.m_x, center.m_y };
            this->m_points = 200;
            this->m_money = 50;
            this->m_moveSpeed = 65.f;
            this->m_moveSpeedNormal = 50.f;
            this->m_health = new Health(60);
        }
        ~StrongEnemy();
};