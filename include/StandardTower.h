#pragma once

#include <vector>

#include "gp/gp.h"
#include "Tower.h"
#include "Resources.h"
#include "Vector2f.h"

class StandardTower : public Tower
{
    private:

    public:
        StandardTower(Vector2f center)
        : Tower(center)
        {
            this->m_name = "StandardTower";
            this->m_color = { 0.8f, 0.7f, 0.6f, 1.f };
            this->m_range = 160.f;
            this->m_fireInterval = 1.3f;
            this->m_timeToFire = m_fireInterval;
            this->m_dmg = 4;
            this->m_position = { center.m_x, center.m_y };
            this->m_target = nullptr;
        }
        
        ~StandardTower();
};