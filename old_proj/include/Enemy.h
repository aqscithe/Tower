#pragma once

#include "gp/gp.h"
#include "Entity.h"
#include "Vector2.h"
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

        Health*     m_health;
        Vector2     m_center = { 0.f, 0.f };
        GPColor     m_color = { 0.f, 0.f, 0.f, 0.f };  
        Vector2     m_direction = { 0.f, 0.f };

    public:
        Enemy(Vector2 center)
        : m_center(center)
        {
            this->updatePosition(m_center.getX(), m_center.getY());
        }
        ~Enemy();

        int         getDmg() const;
        int         getHealth() const;
        int         getMaxHealth() const;
        float       percentHealth() const;
        float       getBarWidth() const;
        float       getBarHeight() const;
        float       getMoveSpeed() const;
        float       getNormalMoveSpeed() const;
        int         getDodgeChance() const;
        float       getDmgReduction() const;
        int         getHealValue() const;
        float       getHealZone() const;
        float       getHealFrequency() const;
        float       getRadius() const;
        bool        hasDied() const;
        Vector2     getCenter() const;
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

        Vector2     getDirection() const;
        void        changeDirection(const Vector2& direction);
        void        updatePosition(float x, float y) override;
        void        loseHealth(int damage);
        void        gainHealth(int healthGained);
};