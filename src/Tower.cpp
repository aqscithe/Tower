#include <time.h>

#include "gp/gp.h"

#include "Tower.h"
#include "Resources.h"
#include "CollisionDetection.h"

#include <iostream>

Tower::~Tower()
{}


int     Tower::getDmg() const
{
    return m_dmg;
}

float   Tower::getFireInterval() const
{
    return m_fireInterval;
}

float   Tower::getRange() const
{
    return m_range;
}

float   Tower::getRadius() const
{
    return m_radius;
}

GPColor     Tower::getColor() const
{
    return m_color;
}

Vector2f   Tower::getCenter() const
{
    return m_center;
}

float   Tower::getExplosionRange() const
{
    return  m_explosionDmg;
}

int     Tower::getExplosionDmg() const
{
    return m_explosionRange;
}

void        Tower::addTarget(Enemy* enemy)
{
    if (m_target == nullptr)
        m_target = enemy;
}

void        Tower::removeTarget()
{
    m_target = nullptr;
}

bool    Tower::isTarget(Enemy* enemy)
{
    /**
    *   REVIEW:
    *   Simplification: return m_target == enemy;
    */

    if (m_target == enemy)
        return true;
    return false;
}

void    Tower::addProjectile(float elapsedTime)
{
    if(m_timeToFire <= 0.f && m_target != nullptr)
    {
        m_timeToFire = m_fireInterval;
        m_projectiles.push_back(new Projectile(m_target, m_name, this->getCenter()));  
    }
    else
        m_timeToFire -= elapsedTime;
}

void    Tower::drawProjectiles(GPLib* gp)
{
    for (Projectile* projectile : m_projectiles)
    {
        GPVector2 center = { projectile->getCenter().m_x, projectile->getCenter().m_y };
        gpDrawCircleFilled(gp, center, projectile->getRadius(), projectile->getColor());
    }
}

void    Tower::moveProjectiles(float elapsedTime)
{
    int index = 0;
    for (Projectile* projectile : m_projectiles)
    {
        // TODO place first 4 lines in a Math function
        Vector2f direction = Math::getVector(projectile->getCenter(), projectile->getTarget()->getCenter());
        direction = Math::getVectorNormal(direction);
        Vector2f newV = { projectile->getPosition().m_x + direction.m_x * projectile->getMoveSpeed() * elapsedTime, projectile->getPosition().m_y + direction.m_y * projectile->getMoveSpeed() * elapsedTime };
        projectile->updatePosition(newV);
        ++index;
    }
}

void     Tower::checkProjectileCollisions(std::vector<Enemy*> enemies, float elapsedTime)
{
    int index = 0;
    for (Projectile* projectile : m_projectiles)
    {
        bool collided = circleToCircleCD
            (
                projectile->getCenter(), projectile->getRadius(), 
                projectile->getTarget()->getCenter(), 
                projectile->getTarget()->getRadius()
            );
        if (collided)
        {
            Enemy* target = projectile->getTarget();
            // first check to see if dodged
            srand(time(NULL));
            int secret = (rand() % (100 - 1 + 1)) + 1;  // (rand() % (max - min + 1)) + min;
            if (secret <= projectile->getTarget()->getDodgeChance())
            {
                std::cout << "ESQUIVÉ!!!" << std::endl;
                std::cout << "Secret: " << secret << std::endl;
            }
            else
            {
                int dmgReceived = (int)(this->m_dmg - this->m_dmg * target->getDmgReduction());
                target->loseHealth(dmgReceived);

                /**
                *   REVIEW:
                *   La comparaison de string est très couteuse! Tu peux plutot utiliser un enum.
                *   La meilleur solution est de faire une fonction virtual ApplyEffect() qui est override dans les enfants!
                */
                if(projectile->getType() == "ExplosiveTower")
                {
                    // do explosive damage to all targets in exlosive range
                    for (Enemy* enemy : enemies)
                    {
                        if ( Math::getDistance(target->getPosition(), enemy->getPosition()) <= this->m_explosionRange )
                        {
                            enemy->loseHealth(this->m_explosionDmg);
                        }
                    }
                }
                else if (projectile->getType() == "SlowingTower")
                {
                    float speed = target->getMoveSpeed();
                    if (speed == target->getNormalMoveSpeed())
                    {
                        target->updateMoveSpeed(speed - speed * this->m_slowPercent, elapsedTime);
                    }    
                }
            }
            // destroy projectile
            std::vector<Projectile*>::iterator it = m_projectiles.begin();
            m_projectiles.erase(it);
        }
        ++index;
    }
    
}