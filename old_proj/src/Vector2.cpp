#include "Vector2.h"

Vector2::Vector2()
{

}

Vector2::Vector2(float x_value, float y_value)
{
    this->m_x = x_value;
    this->m_y = y_value;
}
Vector2::~Vector2()
{

}

float           Vector2::getX() const
{
    return m_x;
}

float           Vector2::getY() const
{
    return m_y;
}

Vector2      Vector2::getPosition() const
{
    return  *this;
}

void            Vector2::updateX(float x)
{
    this->m_x = x;
    return;
}

void    Vector2::updateY(float y)
{
    this->m_y = y;
    return;
}

Vector2& Vector2::operator*(const Vector2& other)
{
    this->m_x *= other.m_x;
    this->m_y *= other.m_y;
    return *this;
}

Vector2&  Vector2::operator+(const Vector2& other)
{
    this->m_x += other.m_x;
    this->m_y += other.m_y;
    return *this;
}

Vector2& Vector2::operator*=(float scalaire)
{
    this->m_x *= scalaire;
    this->m_y *= scalaire;
    return *this;
}

bool Vector2::operator!=(const Vector2 other)
{
    if (this->m_x != other.getX() || this->m_y != other.getY())
        return true;
    return false;
}

bool Vector2::operator==(const Vector2 other)
{
    if (this->m_x == other.getX() && this->m_y == other.getY())
        return true;
    return false;
}
