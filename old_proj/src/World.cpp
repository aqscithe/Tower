#include <iostream>

#include "World.h"
#include "Map.h"
#include "Resources.h"
#include "CollisionDetection.h"

World::World(GPLib* gp)
{
    this->m_gp = gp;
    m_castle = new Castle(300);
}

World::~World()
{
    for (Tower* element : m_tower)
    {
        delete element;
    }
    for (Enemy* element : m_enemy)
    {
        delete element;
    }
}

int World::addTower(float x_pos, float y_pos, int playerMoney, std::string towerName, int price)
{
    if (price <= playerMoney) 
    {
        x_pos += GridBlocks::gridStep;
        y_pos += GridBlocks::gridStep;
        if (towerName == "slowing")
        {
            m_tower.push_back(new SlowingTower({ x_pos, y_pos }));
            return playerMoney - price;
        }
        else if (towerName == "standard")
        {
            m_tower.push_back(new StandardTower({ x_pos, y_pos }));
            return playerMoney - price;
        }
        else if (towerName == "explosive")
        {
            m_tower.push_back(new ExplosiveTower({ x_pos, y_pos }));
            return playerMoney - price;
        }
    }
    else
    {
        std::cout << "NOT ENOUGH MONEY" << std::endl;
        return playerMoney;
    }
    return playerMoney;
}

void        World::drawInactiveTower(Vector2 mousePos, float radius,  GPColor color)
{
    GPVector2 pos = { mousePos.getX() , mousePos.getY() };
    gpDrawCircleFilled(m_gp, pos, radius, color);

}

void    World::drawTowers(GPLib* gp)
{
    bool first = true;
    for (Tower* element : m_tower)
    {
        GPVector2 center = { element->getCenter().getX(), element->getCenter().getY() };
            
        gpDrawCircleFilled(gp, center, element->getRadius(), element->getColor());

        // debugging tower range
        GPColor rangeCircle = { 1.f, 1.f, 1.f, 1.f };
        gpDrawCircle(gp, center, element->getRange(), rangeCircle);
    }
}

void        World::drawTowersStore(GPLib* gp, Vector2 stdPos, Vector2 slowPos, Vector2 expPos)
{
    GPVector2 vector = { stdPos.getX(), stdPos.getY() };
    gpDrawCircleFilled(gp, vector, 15.f, GridBlocks::standardTower);
    vector = { slowPos.getX(), slowPos.getY() };
    gpDrawCircleFilled(gp, vector, 15.f, GridBlocks::slowingTower);
    vector = { expPos.getX(), expPos.getY() };
    gpDrawCircleFilled(gp, vector, 15.f, GridBlocks::explosiveTower);
}

void        World::setCastlePos(int endIndex)
{
    m_castle->setPosition(endIndex);
}

void        World::drawCastle()
{
    gpDrawRectFilled(m_gp, m_castle->getBody(), GridBlocks::castle);
    if (m_castle->getHealth() < m_castle->getMaxHealth())
    {
        // draw red on castle
        GPRect damagedCastle = m_castle->getBody();
        damagedCastle.h *= (float)m_castle->getHealth() / (float)m_castle->getMaxHealth();
        gpDrawRectFilled(m_gp, damagedCastle, GridBlocks::castleDamaged);
    }
    else
    {
        gpDrawRectFilled(m_gp, m_castle->getBody(), GridBlocks::castleDamaged);
    }
}

void    World::spawnEnemy(int startIndex, char enemyChar)
{
    if (enemyChar == 'W')
    {
        m_enemy.push_back(new WeakEnemy(Math::getPositionFromIndex(startIndex)));
        ++m_numEnemies;
    }
    else if (enemyChar == 'S')
    {
        m_enemy.push_back(new StrongEnemy(Math::getPositionFromIndex(startIndex)));
        ++m_numEnemies;
    }
    else if (enemyChar == 'H')
    {
        m_enemy.push_back(new HealingEnemy(Math::getPositionFromIndex(startIndex)));
        ++m_numEnemies;
    }
    
    std::cout << "SPAWNING ENEMY: " << m_numEnemies << std::endl;
}

bool    World::spawnWave(Wave* wave, int startIndex, float enemyTimer)
{
    for (int i = m_nextIndexToSpawn; i < wave->getWaveChars().length(); ++i)
    {
        if (enemyTimer <= 0.f)
        {
            spawnEnemy(startIndex, wave->getWaveChars()[i]);
            m_nextIndexToSpawn = i + 1;
            return false;
        }
        else
        {
            m_nextIndexToSpawn = i;
            return false;
        }  
    }
    m_nextIndexToSpawn = 0;
    return true;
}

void    World::drawEnemies(GPLib* gp)
{
    for (Enemy* element : m_enemy)
    {
        GPVector2 center = { element->getCenter().getX(), element->getCenter().getY() };
        float barWidth = element->getBarWidth() * element->percentHealth();
        GPRect healthBar = 
        { 
            element->getCenter().getX() - barWidth / 2.f, 
            element->getCenter().getY() - element->getRadius() - 0.5f * element->getBarHeight() - 3.f, 
            barWidth, element->getBarHeight() 
        };
        gpDrawCircleFilled(gp, center, element->getRadius(), element->getColor() );
        gpDrawRectFilled(gp, healthBar, GridBlocks::healthBar);

        // TODO: health bar outline
        
    }
}

void    World::drawProjectiles(GPLib* gp)
{
    for (Tower* tower : m_tower)
    {
        tower->drawProjectiles(gp);
    }
}

void    World::moveProjectiles(float elapsedTime)
{
    for (Tower* tower : m_tower)
    {
        tower->moveProjectiles(elapsedTime);
    }
}

void    World::moveEnemies(float elapsedTime, std::string mapChars, int endIndex)
{
    for (Enemy* element : m_enemy)
    {
        Vector2 enemyPos = element->getPosition();
        Vector2 direction = Math::findNextGridPath(mapChars, enemyPos, element->getDirection());
        if (direction != element->getDirection())
            element->changeDirection(direction);

        if (element->getMoveSpeed() < element->getNormalMoveSpeed())
        {
            if (element->getTimeSlowed() >= 2.f)
                element->resetMoveSpeed();
            else
                element->updateMoveSpeed(element->getMoveSpeed(), elapsedTime);
        }

        // direction = Math::getVectorNormal(direction);
        float newX = enemyPos.getX() + direction.getX() * element->getMoveSpeed() * elapsedTime;
        float newY = enemyPos.getY() + direction.getY() * element->getMoveSpeed() * elapsedTime;
        element->updatePosition(newX, newY);
        if (Math::getIndex(element->getPosition()) == endIndex)
            element->updateToFinished();
    }
}

void    World::shootEnemies(float elapsedTime)
{
    for (Tower* tower : m_tower)
    {
        tower->addProjectile(elapsedTime);
    }
}

void     World::healEnemies(float elapsedTime)
{
    for (Enemy* healer : m_enemy)
    {
        if (healer->getHealValue())
        {
            if (healer->getHealTimer() <= 0.f )
            {
                for (Enemy* patient : m_enemy)
                {
                    if ( Math::getDistance(healer->getPosition(), patient->getPosition()) <= healer->getHealZone())
                    {
                        patient->gainHealth(healer->getHealValue());
                    }
                }
                std::cout << "SOIGNER!!!" << std::endl;
                healer->resetHealTimer();
            }
            else
            {
                healer->updateHealTimer(elapsedTime);
            }
        }
    }
}

void    World::checkTowerEnemyCollisions()
{
    for (Tower* tower : m_tower)
    {
        for (Enemy* element : m_enemy)
        {
            bool isTarget = tower->isTarget(element);
            bool collided = circleToCircleCD(tower->getCenter(), tower->getRange(), element->getCenter(), element->getRadius());
            if (collided && !isTarget)
            {
                tower->addTarget(element);
            }
            else if (!collided && isTarget)
            {
                tower->removeTarget();
            }
        }
    }
}

void    World::checkProjectileEnemyCollisions(float elapsedTime)
{
    for (Tower* tower : m_tower)
    {
        tower->checkProjectileCollisions(m_enemy, elapsedTime);
    }
}

Vector2   World::destroyDead()
{
    int index = 0;
    int points = 0;
    int money = 0;
    Vector2 playerUpdate = { 0.f, 0.f };
    for (Enemy* element : m_enemy)
    {
        if(element->hasDied())
        {
            for (Tower* a_tower : m_tower)
            {
                if (a_tower->isTarget(element))
                    a_tower->removeTarget();
            }
            points += element->getPoints();
            money += element->getMoney();
            m_enemy.erase(m_enemy.begin() + index);
        }
        ++index;
    }
    playerUpdate.updateX(points);
    playerUpdate.updateY(money);
    return playerUpdate;
}

void    World::destroyFinished()
{
    int index = 0;
    int damage = 0;
    for (Enemy* element : m_enemy)
    {
        if (element->hasFinished())
        {
            for (Tower* a_tower : m_tower)
            {
                if (a_tower->isTarget(element))
                    a_tower->removeTarget();
            }
            damage += element->getDmg();
            m_enemy.erase(m_enemy.begin() + index);
        }
        ++index;
    }
    m_castle->updateHealth(m_castle->getHealth() - damage);
}

bool    World::isDeserted() const
{
    return m_enemy.empty();
}