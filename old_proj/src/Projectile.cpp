#include "Projectile.h"

Projectile::~Projectile()
{

}

float       Projectile::getRadius() const
{
    return m_radius;
}

GPColor     Projectile::getColor() const
{
    return m_color;
}

Vector2   Projectile::getCenter() const
{
    return m_center;
}

Enemy*      Projectile::getTarget() const
{
    return m_target;
}

float       Projectile::getMoveSpeed() const
{
    return m_moveSpeed;
}

std::string Projectile::getType() const
{
    return m_type;
}

void    Projectile::updatePosition(float x, float y)
{
    this->m_position.updateX(x);
    this->m_position.updateY(y);
    this->m_center = { x, y };
}