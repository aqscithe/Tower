#pragma once

#include <vector>
#include <string>

#include "gp/gp.h"
#include "Tower.h"
#include "Resources.h"
#include "Vector2.h"

class Store : public Entity
{
    private:

        int         m_standardTowerPrice = 30;
        int         m_slowingTowerPrice = 50;
        int         m_explosiveTowerPrice = 100;

        std::string m_stdName = "standard";
        std::string m_slowName = "slowing";
        std::string m_expName = "explosive";

        Vector2     m_stdTowerShopPos = { 0.f, 0.f };
        Vector2     m_expTowerShopPos = { 0.f, 0.f };
        Vector2     m_slwTowerShopPos = { 0.f, 0.f };

        GPColor     m_stdColor = { 0.8f, 0.7f, 0.6f, 1.f };
        GPColor     m_slowColor = { 0.f, 0.39f, 0.7f, 1.f };
        GPColor     m_expColor = { 0.88f, 0.02f, 0.f, 1.f };

        float       m_stdRadius = 15.f;
        float       m_slowRadius = 15.f;
        float       m_expRadius = 15.f;

        GPRect      m_rect = { 0.f, 0.f, 80.f, 300.f };

    public:
        Store();
        ~Store();

        int             getStandardTowerPrice() const;
        int             getSlowingTowerPrice() const;
        int             getExplosiveTowerPrice() const;
        Vector2         getStandardTowerPos() const;
        Vector2         getSlowingTowerPos() const;
        Vector2         getExplosiveTowerPos() const;
        std::string     getStandardName() const;
        std::string     getSlowingName() const;
        std::string     getExplosiveName() const;
        int             getPrice(std::string towerName) const;

        float           getStandardRadius() const;
        float           getSlowingRadius() const;
        float           getExplosiveRadius() const;
        GPColor         getStandardColor() const;
        GPColor         getSlowingColor() const;
        GPColor         getExplosiveColor() const;

        GPRect          getRect() const;
        GPColor         getColor() const;


};