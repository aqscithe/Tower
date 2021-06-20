#pragma once

#include <vector>

#include "gp/gp.h"
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Vector2f.h"

class Projectile;
class Tower : public Entity
{
    protected:
        std::vector<Projectile*>    m_projectiles;

        int         m_dmg = 0;
        float       m_radius = 15.f;
        float       m_fireInterval = 0.f; // second
        float       m_timeToFire = 0.f;
        float       m_range = 0.f;
        float       m_explosionRange = 0.f; 
        int         m_explosionDmg = 0;
        float       m_slowPercent = 0.f;
        float       m_slowTime = 0.f;
        Vector2f     m_center = { 0.f, 0.f };
        GPColor     m_color = { 0.f, 0.f, 0.f, 0.f };
        Enemy*      m_target = nullptr;


    public:
        /**
        *   REVIEW: Utilise const Vector2f& pour eviter une copie!
        */
        Tower(Vector2f center)
        : m_center(center)
        {}
        ~Tower();

        /**
        *   REVIEW:
        *   Simplification: variables const en public.
        */
        int         getDmg() const;
        float       getFireInterval() const;
        float       getRange() const;
        float       getRadius() const;
        GPColor     getColor() const;
        Vector2f     getCenter() const;

        float       getExplosionRange() const;
        int         getExplosionDmg() const;

        bool        isTarget(Enemy* enemy);

        void        addTarget(Enemy* enemy);
        void        removeTarget();
        void        addProjectile(float elapsedTime);

        void        drawProjectiles(GPLib* gp);
        void        moveProjectiles(float elapsedTime);
        void        checkProjectileCollisions(std::vector<Enemy*> enemies, float elapsedTime);

};