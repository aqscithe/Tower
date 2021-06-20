#pragma once

#include <vector>
#include <string>

#include "gp/gp.h"
#include "Tower.h"
#include "Vector2.h"

class Vector2;
class Enemy;
class Projectile : public Entity
{
    private:
        float           m_moveSpeed = 300.f;
        float           m_radius = 5.f;
        Vector2         m_center = { 0.f, 0.f };
        GPColor         m_color = { 0.f, 1.f, 0.f, 1.f };
        std::string     m_type = "";
        Enemy*          m_target = nullptr;

    public:
        Projectile(Enemy* enemy, std::string name, Vector2 center)
        : m_target(enemy), m_type(name), m_center(center)
        {
            this->updatePosition(center.getX(), center.getY());
        }
        
        ~Projectile();

        float           getRadius() const;
        float           getMoveSpeed() const;
        Vector2         getCenter() const;
        GPColor         getColor() const;
        std::string     getType() const;

        Enemy*          getTarget() const;

        void            updatePosition(float x, float y) override;

};