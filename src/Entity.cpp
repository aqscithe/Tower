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

void    Entity::updatePosition(const Vector2f& vector)
{
    m_position.m_x = vector.m_x;
    m_position.m_y = vector.m_y;
}

Vector2f   Entity::getPosition()
{
    return m_position;
}

