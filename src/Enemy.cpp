#include "Enemy.h"

Enemy::~Enemy()
{
    /**
    *   REVIEW:
    *   Ou est l'init?
    *   m_health appartient a Enemy, c'est lui qui devrait gérer la création / destruction.
    */
    delete m_health;
}

int     Enemy::getDmg() const
{
    return m_dmg;
}

int   Enemy::getHealth() const
{
    return m_health->getCurrentHealth();
}

int   Enemy::getMaxHealth() const
{
    return m_health->getMaxHealth();
}

float  Enemy::getBarWidth() const
{
    return m_health->getBarWidth();
}

float   Enemy::getBarHeight() const
{
    return m_health->getBarHeight();
}

float     Enemy::percentHealth() const
{
    return (float)m_health->getCurrentHealth() / (float)m_health->getMaxHealth();
}

float   Enemy::getMoveSpeed() const
{
    return m_moveSpeed;
}

float   Enemy::getNormalMoveSpeed() const
{
    return m_moveSpeedNormal;
}

Vector2f   Enemy::getCenter() const
{
    return m_center;
}

float       Enemy::getRadius() const
{
    return m_radius;
}

GPColor     Enemy::getColor() const
{
    return m_color;
}

int       Enemy::getDodgeChance() const
{
    return m_dodgeChance;
}

float       Enemy::getTimeSlowed() const
{
    return m_timeSlowed;
}

float       Enemy::getDmgReduction() const
{
    return m_dmgReduction;
}

int     Enemy::getHealValue() const
{
    return m_healValue;
}

float   Enemy::getHealZone() const
{
    return m_healZone;
}

float    Enemy::getHealTimer() const
{
    return m_healTimer;
}

bool     Enemy::hasDied() const
{
    return m_isDead;
}

bool        Enemy::hasFinished() const
{
    return m_finished;
}

void        Enemy::updateToFinished()
{
    m_finished = true;
}

void        Enemy::updateMoveSpeed(float newMoveSpeed, float elapsedTime)
{
    m_moveSpeed = newMoveSpeed;
    m_timeSlowed += elapsedTime;
}

void        Enemy::resetMoveSpeed()
{
    m_moveSpeed = m_moveSpeedNormal;
    m_timeSlowed = 0.f;
}

void       Enemy::loseHealth(int damage)
{
    m_health->updateHealth(-damage);

    /**
    *   REVIEW:
    *   Good idea or add a IsDead() {return m_currentLife <= 0} method.
    */
    // better to have a get function or add a <= operator function to Health class?
    // then i could just do m_health <= 0.
    if (m_health->getCurrentHealth() <= 0)
        m_isDead = true;
}

void        Enemy::resetHealTimer()
{
    m_healTimer = m_healFrequency;
}

void        Enemy::updateHealTimer(float elapsedTime)
{
    m_healTimer -= elapsedTime;
}

void        Enemy::gainHealth(int healthGained)
{
    m_health->updateHealth(healthGained);
}

void    Enemy::updatePosition(const Vector2f& vector)
{
    m_position.set(vector.m_x, vector.m_y);
    m_center.set(vector.m_x, vector.m_y);
}

Vector2f  Enemy::getDirection() const
{
    return this->m_direction;
}
        
void      Enemy::changeDirection(const Vector2f& direction)
{
    this->m_direction = direction;
}

int         Enemy::getPoints()  const
{
    return m_points;
}

int         Enemy::getMoney()  const
{
    return m_money;
}