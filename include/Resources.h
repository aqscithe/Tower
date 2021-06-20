#pragma once

#include <string>

#include "gp/gp.h"
#include "Vector2f.h"

namespace GridBlocks
{
    extern int         gridStep;
    extern int         gridColumns;
    extern int         gridRows;

    /**
    *   REVIEW:
    *   A definir dans le fichier GPColor.h
    */
    extern GPColor     blocked;
    extern GPColor     path;
    extern GPColor     towerSlot;
    extern GPColor     explosiveTower;
    extern GPColor     standardTower;
    extern GPColor     slowingTower;
    extern GPColor     healthBar;
    extern GPColor     castle;
    extern GPColor     castleDamaged;

    /**
    *   REVIEW:
    *   A definir dans le fichier Vector2f.h idealement:
    * 
    *   struct Vector2f
    *   {
    *       // code...
    * 
    *       static const Vector2f up;
    *   };
    */
    extern const Vector2f null;
    extern const Vector2f up;
    extern const Vector2f down;
    extern const Vector2f left;
    extern const Vector2f right;
    extern const Vector2f upperLeft;
    extern const Vector2f lowerLeft;
    extern const Vector2f upperRight;
    extern const Vector2f lowerRight;

    enum class gridStates : char;

    bool        isOnPath(int index, std::string mapChars);
};

namespace Math
{
    bool        pointInsideRect(GPVector2 position, GPRect rect);


    /**
    *   REVIEW: Utilise const Vector2f& pour eviter une copie.
    *   A definir dans la class Vector2f.
    */
    Vector2f     getVector(Vector2f coord_a, Vector2f coord_b);

    /** REVIEW: Same. */
    float       getVecMagnitude(const Vector2f& vector);

    float       dotProduct(const Vector2f& vectorA, const Vector2f& vectorB);

    /** REVIEW: Same. */
    float       getDistance(const Vector2f& vectorA, const Vector2f& vectorB);

    /** REVIEW: Same. */
    Vector2f     getVectorNormal(const Vector2f& vector);

    int         getIndex(const Vector2f& vector);

    Vector2f     getDirectionVector(int enemyIndex, std::string mapChars, Vector2f enemyDirection);

    Vector2f     findNextGridPath(std::string mapChars, Vector2f& position, const Vector2f& direction);

    /** REVIEW: Same. */
    Vector2f     getOppositeVector(Vector2f vector);

    /** REVIEW: Same. */
    bool        hasReachedCenter(Vector2f position, Vector2f enemyDirection);

    Vector2f     getPositionFromIndex(int index);

    int         getIndexUp(int index);
    int         getIndexDown(int index);
    int         getIndexLeft(int index);
    int         getIndexRight(int index);

};





