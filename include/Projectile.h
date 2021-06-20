#pragma once

#include <vector>
#include <string>

#include "gp/gp.h"
#include "Tower.h"
#include "Vector2f.h"

class Vector2f;
class Enemy;
class Projectile : public Entity
{
    private:
        float           m_moveSpeed = 300.f;
        float           m_radius = 5.f;
        Vector2f         m_center = { 0.f, 0.f };
        GPColor         m_color = { 0.f, 1.f, 0.f, 1.f };
        std::string     m_type = "";
        Enemy*          m_target = nullptr;

    public:
        /**
        *   REVIEW:
        *   Evite le code dans le .h
        *   Utilise const std::string& et const Vector2f& pour eviter une copie.
        */
        Projectile(Enemy* enemy, std::string name, Vector2f center)
        : m_target(enemy), m_type(name), m_center(center)
        {
            this->updatePosition(center);
        }
        
        ~Projectile();

        /**
        *   REVIEW:
        *   Simplification: variables const en public.
        */
        float           getRadius() const;
        float           getMoveSpeed() const;
        Vector2f         getCenter() const;
        GPColor         getColor() const;
        std::string     getType() const;

        Enemy*          getTarget() const;

        /** REVIEW: Utilise const Vector2f& en parametre. */
        void            updatePosition(const Vector2f& vector) override;

};