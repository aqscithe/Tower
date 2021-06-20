#include <math.h>

#include "CollisionDetection.h"

float getDistance(const Vector2 vectorA, const Vector2 vectorB)
{
    return (float) (sqrt (pow ( vectorA.getX() - vectorB.getX(), 2 ) + pow ( vectorA.getY() - vectorB.getY(), 2 )));
}

bool circleToCircleCD(const Vector2 vectorA, float radiusA, const Vector2 vectorB, float radiusB)
{
    float centerDistance = getDistance(vectorA, vectorB);
    float radiusSum = radiusA + radiusB;
    if (centerDistance < radiusSum)
        return true;
    return false;
}