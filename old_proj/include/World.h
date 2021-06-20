#pragma once

#include <vector>

#include "gp/gp.h"
#include "StandardTower.h"
#include "ExplosiveTower.h"
#include "SlowingTower.h"
#include "Tower.h"
#include "WeakEnemy.h"
#include "StrongEnemy.h"
#include "HealingEnemy.h"
#include "Enemy.h"
#include "Vector2.h"
#include "Castle.h"
#include "Wave.h"



class World
{
    private:
        std::vector<Enemy*>         m_enemy;
        std::vector<Tower*>         m_tower;
        Castle*                     m_castle;
        int                         m_numEnemies = 0;
        int                         m_nextIndexToSpawn = 0;
        GPLib*                      m_gp;

    public:
        World(GPLib* gp);
        ~World();

        void        drawTowers(GPLib* gp);
        void        drawTowersStore(GPLib* gp, Vector2, Vector2, Vector2);
        int         addTower(float x_pos, float y_pos, int playerMoney, std::string towerName, int price); 
        void        drawInactiveTower(Vector2 mousePos, float radius, GPColor color);

        void        setCastlePos(int endIndex);
        void        drawCastle();

        void        drawEnemies(GPLib* gp);
        void        spawnEnemy(int startIndex, char enemyChar);
        bool        spawnWave(Wave* wave, int startIndex, float enemyTimer);

        void        drawProjectiles(GPLib* gp);

        void        checkTowerEnemyCollisions();
        void        checkProjectileEnemyCollisions(float elapsedTime);
        void        moveEnemies(float elapsedTime, std::string mapChars, int endIndex);
        void        moveProjectiles(float elapsedTime);
        void        shootEnemies(float elapsedTime);
        void        healEnemies(float elapsedTime);
        Vector2     destroyDead();
        void        destroyFinished();
        void        moveTower(GPVector2 mousePos);
        bool        isDeserted() const;

};