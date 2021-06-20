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
    Vector2 endPos = Math::getPositionFromIndex(endIndex);
    this->updatePosition(endPos.getX(), endPos.getY());
    this->m_body.x = this->getPosition().getX() + 0.5f * GridBlocks::gridStep;
    this->m_body.y = this->getPosition().getY() - 0.75f * GridBlocks::gridStep;
}

Castle& Castle::operator=(const Castle& castle)
{
    this->m_health = castle.m_health;
    return *this;
}