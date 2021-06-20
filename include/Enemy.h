#pragma once

#include "gp/gp.h"
#include "Entity.h"
#include "Vector2f.h"
#include "Health.h"

class Enemy : public Entity
{
    protected:
        int         m_dmg = 0; // TODO: change name
        int         m_points = 0;
        int         m_money = 0;
        float       m_moveSpeed = 80.f;
        float       m_moveSpeedNormal = 80.f;
        int         m_dodgeChance = 0;
        float       m_dmgReduction = 0.f;
        int         m_healValue = 0; 
        float       m_healZone = 0.f;
        float       m_healFrequency = 0.f;
        float       m_healTimer = 0.f;
        bool        m_isDead = false;
        bool        m_finished = false;
        float       m_radius = 10.f;
        float       m_timeSlowed = 0.f;

        Health*     m_health; /** REVIEW: Init nullptr. */
        Vector2f     m_center = { 0.f, 0.f };
        GPColor     m_color = { 0.f, 0.f, 0.f, 0.f };  
        Vector2f     m_direction = { 0.f, 0.f };

    public:
        /**
        *   REVIEW:
        *   Code dans le .h
        *   Utilise const Vector2f& pour eviter une copie.
        */
        Enemy(Vector2f center)
        : m_center(center)
        {
            this->updatePosition(center);
        }
        ~Enemy();

        int         getDmg() const;

        /**
        *   REVIEW:
        *   Simplification:
        *   1. const Health* GetHealth(); puis call les fonctions directement depuis Health*
        *   2. en public const Health* m_health.
        */
        int         getHealth() const;
        int         getMaxHealth() const;
        float       percentHealth() const;
        float       getBarWidth() const;
        float       getBarHeight() const;

        /**
        *   REVIEW:
        *   Simplification:
        *   déclare tes variables const en public.
        *   Ex:
        *   public:
        *       const float m_moveSpeed = 80.f;
        */
        float       getMoveSpeed() const;
        float       getNormalMoveSpeed() const;
        int         getDodgeChance() const;
        float       getDmgReduction() const;
        int         getHealValue() const;
        float       getHealZone() const;
        float       getHealFrequency() const;
        float       getRadius() const;
        bool        hasDied() const;
        Vector2f     getCenter() const;
        GPColor     getColor() const;
        int         getPoints() const;
        int         getMoney() const;
        bool        hasFinished() const;
        void        updateToFinished();
        void        updateMoveSpeed(float newMoveSpeed, float elpasedTime);
        void        resetMoveSpeed();
        void        resetHealTimer();
        void        updateHealTimer(float elapsedTime);
        float       getHealTimer() const;
        float       getTimeSlowed() const;

        Vector2f     getDirection() const;
        void        changeDirection(const Vector2f& direction);

        /**
        *   REVIEW:
        *   Passe un const Vector2f& en parametre.
        */
        void        updatePosition(const Vector2f& vector) override;
        void        loseHealth(int damage);
        void        gainHealth(int healthGained);
};