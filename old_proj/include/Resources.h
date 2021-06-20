#pragma once

#include <string>

#include "gp/gp.h"
#include "Vector2.h"

namespace GridBlocks
{
    extern int         gridStep;
    extern int         gridColumns;
    extern int         gridRows;

    extern GPColor     blocked;
    extern GPColor     path;
    extern GPColor     towerSlot;
    extern GPColor     explosiveTower;
    extern GPColor     standardTower;
    extern GPColor     slowingTower;
    extern GPColor     healthBar;
    extern GPColor     castle;
    extern GPColor     castleDamaged;

    extern const Vector2 null;
    extern const Vector2 up;
    extern const Vector2 down;
    extern const Vector2 left;
    extern const Vector2 right;
    extern const Vector2 upperLeft;
    extern const Vector2 lowerLeft;
    extern const Vector2 upperRight;
    extern const Vector2 lowerRight;

    enum class gridStates : char;

    bool        isOnPath(int index, std::string mapChars);
};

namespace Math
{
    bool        pointInsideRect(GPVector2 position, GPRect rect);

    Vector2     getVector(Vector2 coord_a, Vector2 coord_b);

    float       getVecMagnitude(const Vector2 vector);

    float       getDistance(const Vector2 vectorA, const Vector2 vectorB);

    Vector2     getVectorNormal(Vector2 vector);

    int         getIndex(const Vector2& vector);

    Vector2     getDirectionVector(int enemyIndex, std::string mapChars, Vector2 enemyDirection);

    Vector2     findNextGridPath(std::string mapChars, Vector2& position, const Vector2& direction);

    Vector2     getOppositeVector(Vector2 vector);

    bool        hasReachedCenter(Vector2 position, Vector2 enemyDirection);

    Vector2     getPositionFromIndex(int index);

    int         getIndexUp(int index);
    int         getIndexDown(int index);
    int         getIndexLeft(int index);
    int         getIndexRight(int index);

};





