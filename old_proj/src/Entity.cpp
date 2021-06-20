#include "Entity.h"

unsigned int Entity::m_entityCount = 0;

Entity::Entity()
{
    ++m_entityCount;
}

Entity::~Entity()
{
    --m_entityCount;
}

void    Entity::draw(GPLib* gp)
{}

void    Entity::increaseEntities()
{
    ++m_entityCount;
}

void    Entity::updatePosition(float x, float y)
{
    this->m_position.updateX(x);
    this->m_position.updateY(y);
}

Vector2   Entity::getPosition()
{
    return m_position;
}

