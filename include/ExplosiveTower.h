#pragma once

#include "gp/gp.h"
#include "Tower.h"

class ExplosiveTower : public Tower
{
    private:

    public:
        ExplosiveTower(Vector2f m_center)
        : Tower(m_center)
        {
            this->m_name = "ExplosiveTower";
            this->m_color = { 0.88f, 0.02f, 0.f, 1.f };
            this->m_range = 160.f;
            this->m_fireInterval = 4.f;
            this->m_timeToFire = m_fireInterval;
            this->m_dmg = 7;
            this->m_position = { m_center.m_x, m_center.m_y };
            this->m_target = nullptr;
            this->m_explosionRange =  100.f;
            this->m_explosionDmg = 3;
        }
        ~ExplosiveTower();

        void    draw(GPLib*) ;
};