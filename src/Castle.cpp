#include <iostream>

#include "Castle.h"

Castle::~Castle()
{
}

void    Castle::updateHealth(int updatedHealth)
{
    if (updatedHealth <= 0)
    {
        m_health = 0;
        return;
    }
    if (updatedHealth != m_health)
    {
        m_health = updatedHealth;
        std::cout << "UPDATED Health " << m_health << std::endl;
    }
}

int     Castle::getHealth() const
{
    return m_health;
}

int     Castle::getMaxHealth() const
{
    return m_maxHealth;
}

GPRect  Castle::getBody() const
{
    return m_body;
}

void     Castle::setPosition(int endIndex)
{
    Vector2f endPos = Math::getPositionFromIndex(endIndex);
    this->updatePosition(endPos);
    this->m_body.x = this->getPosition().m_x + 0.5f * GridBlocks::gridStep;
    this->m_body.y = this->getPosition().m_y - 0.75f * GridBlocks::gridStep;
}

Castle& Castle::operator=(const Castle& castle)
{
    this->m_health = castle.m_health;
    return *this;
}