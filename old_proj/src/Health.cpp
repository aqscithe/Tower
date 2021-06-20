#include "Health.h"

Health::~Health()
{}

int         Health::getCurrentHealth() const
{
    return m_currentLife;
}

int         Health::getMaxHealth() const
{
    return m_maxLife;
}

void     Health::updateHealth(int healthChange)
{
    if (m_currentLife + healthChange >= this->getMaxHealth())
    {
        m_currentLife = this->getMaxHealth();
        return;
    }
    m_currentLife += healthChange;
}

float   Health::getBarWidth() const
{
    return m_width;
}

float   Health::getBarHeight() const
{
    return m_height;
}