#pragma once

#include "gp/gp.h"

class Vector2
{
    private:
        float m_x = 0.f;
        float m_y = 0.f;

    public:
        Vector2();
        Vector2(float x, float y);

        ~Vector2();

        float           getX() const;
        float           getY() const;
        Vector2         getPosition() const;

        void            updateX(float x);
        void            updateY(float y);

        Vector2&        operator*(const Vector2& other);
        Vector2&        operator+(const Vector2& other);  
        Vector2&        operator*=(float scalaire);
        bool            operator!=(const Vector2 other);
        bool            operator==(const Vector2 other);
};