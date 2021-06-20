
#pragma once

#include "gp/gp.h"
#include "Tower.h"

class SlowingTower : public Tower
{
    private:

    public:
        SlowingTower(Vector2f center)
        : Tower(center)
        {
            this->m_name = "SlowingTower";
            this->m_color = { 0.f, 0.39f, 0.7f, 1.f };
            this->m_range = 160.f;
            this->m_fireInterval = 2.8f;
            this->m_timeToFire = m_fireInterval;
            this->m_dmg = 1;
            this->m_slowPercent = 0.35f;
            this->m_slowTime = 3.f;
            this->m_position = { center.m_x, center.m_y };
            this->m_target = nullptr;
        }
        ~SlowingTower();

        void    draw(GPLib*) ;
};