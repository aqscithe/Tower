#include <math.h>
#include <iostream>

#include "Resources.h"
#include "Screen.h"



int         GridBlocks::gridStep = 40;
int         GridBlocks::gridColumns = SCREEN_WIDTH / GridBlocks::gridStep;
int         GridBlocks::gridRows = SCREEN_HEIGHT / GridBlocks::gridStep;

GPColor     GridBlocks::blocked =  { 0.f, 0.f, 0.f, 1.f };
GPColor     GridBlocks::path =  { 0.f, 0.f, 1.f, 1.f };

// if tower slots are white i can't place a tower there...
GPColor     GridBlocks::towerSlot =  { 0.f, 1.f, 1.f, 1.f }; 

GPColor     GridBlocks::explosiveTower = { 0.88f, 0.02f, 0.f, 1.f };
GPColor     GridBlocks::standardTower = { 0.8f, 0.7f, 0.6f, 1.f };
GPColor     GridBlocks::slowingTower = { 0.f, 0.39f, 0.7f, 1.f };
GPColor     GridBlocks::healthBar = { 0.14f, 1.f, 0.f, 1.f };
GPColor     GridBlocks::castle = { 0.75f, 0.75f, 0.75f, 1.f }; 
GPColor     GridBlocks::castleDamaged = { 1.f, 0.f, 0.f, 1.f };

const Vector2     GridBlocks::null = { 0.f, 0.f };
const Vector2     GridBlocks::up = { 0.f, -1.f };
const Vector2     GridBlocks::down = { 0.f, 1.f };
const Vector2     GridBlocks::left = { -1.f, 0.f };
const Vector2     GridBlocks::right = { 1.f, 0.f };
const Vector2     GridBlocks::upperLeft = { -1.f, -1.f };
const Vector2     GridBlocks::lowerLeft = { -1.f, 1 };
const Vector2     GridBlocks::upperRight = { 1.f, -1.f };
const Vector2     GridBlocks::lowerRight = { 1.f, 1.f };



enum class GridBlocks::gridStates : char
{
    BLOCKED = 'X',
    PATH = 'D',
    TOWERSLOT = 'O'
};

bool Math::pointInsideRect(GPVector2 position, GPRect rect)
{
    float halfWidth = 0.5f * rect.w;
    // the position of the x and y is the top left corner of each block instead of the center...not sure why
    // so i'm fixing it with newX and newY
    float newX = rect.x + rect.w;
    float newY = rect.y + rect.w;
    if 
        (
            position.x >= newX - halfWidth &&
            position.x <= newX + halfWidth &&
            position.y >= newY - halfWidth &&
            position.y <= newY + halfWidth
        )
    {
        return true;
    }
    return false;
}

Vector2 Math::getVector(Vector2 coord_a, Vector2 coord_b)
{
    Vector2 vector = { coord_b.getX() - coord_a.getX(), coord_b.getY() - coord_a.getY() };
    return vector;
}

float Math::getVecMagnitude(const Vector2 vector)
{
    return (sqrtf ( powf ( vector.getX(), 2 ) + powf ( vector.getY(), 2 ) ));
}

float Math::getDistance(const Vector2 vectorA, const Vector2 vectorB)
{
    return sqrtf (powf ( vectorA.getX() - vectorB.getX(), 2 ) + powf ( vectorA.getY() - vectorB.getY(), 2 ));
}

Vector2  Math::getVectorNormal(Vector2 vector)
{
    Vector2 vectorNormal = { 0.f, 0.f };
    float magnitude = Math::getVecMagnitude(vector);

    vectorNormal.updateX(vector.getX() / magnitude);
    vectorNormal.updateY(vector.getY() / magnitude);

    return vectorNormal;
}

int         Math::getIndex(const Vector2& vector)
{
    int x_block = ((int)(vector.getX()) / GridBlocks::gridStep);
    int y_block = ((int)(vector.getY()) / GridBlocks::gridStep);
    return (x_block + y_block * GridBlocks::gridColumns);
}

bool        GridBlocks::isOnPath(int index, std::string mapChars)
{
    if (mapChars[index] == 'P' || mapChars[index] == 'E')
        return true;
    return false;
}

Vector2    Math::getOppositeVector(Vector2 vector)
{
    float magnitude = getVecMagnitude(vector);
    vector *= (-1 / magnitude);
    return vector;
}

Vector2     Math::getPositionFromIndex(int index)
{
    float x = (float) (index % GridBlocks::gridColumns * GridBlocks::gridStep);
    float y = (float) (index / GridBlocks::gridColumns * GridBlocks::gridStep + (0.5f * GridBlocks::gridStep));
    return { x, y };
}

int         Math::getIndexUp(int index)
{
    return index - GridBlocks::gridColumns;
}

int         Math::getIndexDown(int index)
{
    return index + GridBlocks::gridColumns;
}

int         Math::getIndexLeft(int index)
{
    return index - 1;
}

int         Math::getIndexRight(int index)
{
    return index + 1;
}

Vector2     Math::getDirectionVector(int enemyIndex, std::string mapChars, Vector2 enemyDirection)
{
    int indexUp = Math::getIndexUp(enemyIndex);
    int indexDown = Math::getIndexDown(enemyIndex);
    int indexLeft = Math::getIndexLeft(enemyIndex);
    int indexRight = Math::getIndexRight(enemyIndex);

    if(enemyDirection == GridBlocks::null)
    {
        if(GridBlocks::isOnPath(indexDown, mapChars))
            return GridBlocks::down;
        if(GridBlocks::isOnPath(indexLeft, mapChars))
            return GridBlocks::left;
        if(GridBlocks::isOnPath(indexRight, mapChars))
            return GridBlocks::right;
        if(GridBlocks::isOnPath(indexUp, mapChars))
            return GridBlocks::up;
    }
    else if (enemyDirection == GridBlocks::down)
    {
        // DO NOT check block above
        if(GridBlocks::isOnPath(indexDown, mapChars))
            return GridBlocks::down;
        if(GridBlocks::isOnPath(indexLeft, mapChars))
            return GridBlocks::left;
        if(GridBlocks::isOnPath(indexRight, mapChars))
            return GridBlocks::right;
    }
    else if (enemyDirection == GridBlocks::up)
    {
        // do not check block below
        if(GridBlocks::isOnPath(indexUp, mapChars))
            return GridBlocks::up;
        if(GridBlocks::isOnPath(indexLeft, mapChars))
            return GridBlocks::left;
        if(GridBlocks::isOnPath(indexRight, mapChars))
            return GridBlocks::right;
    }
    else if (enemyDirection == GridBlocks::left)
    {
        // do not check block to the right
        if(GridBlocks::isOnPath(indexLeft, mapChars))
            return GridBlocks::left;
        if(GridBlocks::isOnPath(indexUp, mapChars))
            return GridBlocks::up;
        if(GridBlocks::isOnPath(indexLeft, mapChars))
            return GridBlocks::left;
    }
    else if (enemyDirection == GridBlocks::right)
    {
        // do not check block to the left
        if(GridBlocks::isOnPath(indexRight, mapChars))
            return GridBlocks::right;
        if(GridBlocks::isOnPath(indexDown, mapChars))
            return GridBlocks::down;
        if(GridBlocks::isOnPath(indexUp, mapChars))
            return GridBlocks::up;
    }

    return { 0.f, 0.f };
}

bool Math::hasReachedCenter(Vector2 position, Vector2 enemyDirection)
{
    int     indexNextBlock = 0;
    if (enemyDirection == GridBlocks::down)
    {
        indexNextBlock = Math::getIndex(position);
        if (position.getY() >= Math::getPositionFromIndex(indexNextBlock).getY())
            return true;
    }
    else if (enemyDirection == GridBlocks::up)
    {
        indexNextBlock = Math::getIndex(position);
        if (position.getY() <= Math::getPositionFromIndex(indexNextBlock).getY())
            return true;
    }
    else if (enemyDirection == GridBlocks::left)
    {
        indexNextBlock = Math::getIndex(position);
        if (position.getX() <= Math::getPositionFromIndex(indexNextBlock).getX() + 0.5f * GridBlocks::gridColumns)
            return true;
    }
    else if (enemyDirection == GridBlocks::right)
    {
        indexNextBlock = Math::getIndex(position);
        if( position.getX() >= Math::getPositionFromIndex(indexNextBlock).getX() + 0.5f * GridBlocks::gridColumns)
            return true;
    }
    return false;
}

Vector2     Math::findNextGridPath(std::string mapChars, Vector2& enemyPos, const Vector2& enemyDirection)
{
    Vector2 direction = enemyDirection;
    if (Math::hasReachedCenter(enemyPos, enemyDirection) || direction == GridBlocks::null)
    {
        direction = Math::getDirectionVector(Math::getIndex(enemyPos), mapChars, enemyDirection);
    }
    return direction;
        
}

