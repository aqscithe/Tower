#include "Store.h"
#include "Resources.h"

Store::Store()
{
    Vector2 pos = Math::getPositionFromIndex(64);
    this->updatePosition(pos.getX(), pos.getY());
    this->m_rect.x = getPosition().getX();
    this->m_rect.y = getPosition().getY();
    this->m_fill = { 0.94f, 0.95f, 1.f, 0.4f };
    this->m_stdTowerShopPos = {m_rect.x + 0.5f * m_rect.w, m_rect.y + 0.25f * m_rect.h};
    this->m_slwTowerShopPos = {m_rect.x + 0.5f * m_rect.w, m_rect.y + 0.5f * m_rect.h};
    this->m_expTowerShopPos = {m_rect.x + 0.5f * m_rect.w, m_rect.y + 0.75f * m_rect.h};
}

Store::~Store()
{}

int     Store::getStandardTowerPrice() const
{
    return m_standardTowerPrice;
}

int     Store::getSlowingTowerPrice() const
{
    return m_slowingTowerPrice;
}

int     Store::getExplosiveTowerPrice() const
{
    return m_explosiveTowerPrice;
}

GPRect  Store::getRect() const
{
    return m_rect;
}

GPColor     Store::getColor() const
{
    return m_fill;
}

Vector2     Store::getStandardTowerPos() const
{
    return m_stdTowerShopPos;
}

Vector2     Store::getSlowingTowerPos() const
{
    return m_slwTowerShopPos;
}

Vector2     Store::getExplosiveTowerPos() const
{
    return m_expTowerShopPos;
}

std::string     Store::getStandardName() const
{
    return m_stdName;
}

std::string     Store::getSlowingName() const
{
    return m_slowName;
}

std::string     Store::getExplosiveName() const
{
    return m_expName;
}

float    Store::getStandardRadius() const
{
    return m_stdRadius;
}

float     Store::getSlowingRadius() const
{
    return m_slowRadius;
}

float     Store::getExplosiveRadius() const
{
    return m_expRadius;
}

GPColor     Store::getStandardColor() const
{
    return m_stdColor;
}

GPColor     Store::getSlowingColor() const
{
    return m_slowColor;
}

GPColor     Store::getExplosiveColor() const
{
    return m_expColor;
}

int         Store::getPrice(std::string towerName) const
{
    if (towerName == m_slowName)
        return m_slowingTowerPrice;
    if (towerName == m_stdName)
        return m_standardTowerPrice;
    if (towerName == m_expName)
        return m_explosiveTowerPrice;
    return -1;
}