/**
* REVIEW: Manque #pragma once.
*/

#include <gp/gp.h>

#include "Vector2f.h"

/**
*	REVIEW:
*	Utilise const Vector2f& pour éviter une copie!
*/
float getDistance(const Vector2f coordA, const Vector2f coordB);

/**
*	REVIEW:
*	Utilise const Vector2f& pour éviter une copie!
*/
bool circleToCircleCD(const Vector2f vectorA, float radiusA, const Vector2f vectorB, float radiusB);