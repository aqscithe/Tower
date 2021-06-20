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

Vector2f   Projectile::getCenter() const
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

void    Projectile::updatePosition(const Vector2f& vector)
{
    m_position.set(vector.m_x, vector.m_y);
    m_center.set(vector.m_x, vector.m_y);
}