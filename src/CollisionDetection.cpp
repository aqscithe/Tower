#include <math.h>

#include "CollisionDetection.h"

float getDistance(const Vector2f vectorA, const Vector2f vectorB)
{
    /**
    *   REVIEW: Indentation:
    *   (float)(sqrt(pow(vectorA.m_x - vectorB.m_x, 2) + pow(vectorA.m_y - vectorB.m_y, 2)));
    */
    return sqrtf(powf(vectorA.m_x - vectorB.m_x, 2 ) + powf(vectorA.m_y - vectorB.m_y, 2 ));
}

bool circleToCircleCD(const Vector2f vectorA, float radiusA, const Vector2f vectorB, float radiusB)
{
    /**
    *   REVIEW:
    *   Simplification:
    *   return getDistance(vectorA, vectorB) < radiusA + radiusB;
    */
    return getDistance(vectorA, vectorB) < radiusA + radiusB;
}