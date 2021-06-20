#include <iostream>

#include "Game.h"
#include "Vector2f.h"
#include "Resources.h"

Game::Game(GPLib* gp)
{
    m_map = new Map();
    m_world = new World(gp);
    m_store = new Store();
    m_player = new Player(300, 0);
    m_waveManager = new WaveManager();
}

Game::~Game()
{
    delete m_map;
    delete m_world;
    delete m_store;
    delete m_player;
    delete m_waveManager;
}

void    Game::addToMap(std::string line, int row)
{
    float floatGrid = (float)GridBlocks::gridStep;
    GPRect      grid; /** REVIEW: Indentation. */
    
    for (int i = 0; i < line.length(); ++i)
    {
        /**
        *   REVIEW:
        *   "this->" pas n�c�ssaire:
        *   m_mapChars += line[i];
        */
        this->m_mapChars += line[i];
        grid = 
            { (i * floatGrid) - (0.5f * floatGrid), 
                (row * floatGrid) - (0.5f * floatGrid), 
                floatGrid, floatGrid 
            };
        switch (line[i])
        {
            case 'X' :
                m_map->addGrid(i, grid, GridBlocks::blocked);
                break;
            case 'P' :
                m_map->addGrid(i, grid, GridBlocks::path);
                break;
            case 'T' :
                m_map->addGrid(i, grid, GridBlocks::towerSlot);
                break;
            case 'S' :
                m_startIndex = i + row * GridBlocks::gridColumns;
                m_map->addGrid(i, grid, GridBlocks::path);
                break;
            case 'E' :
                m_endIndex = i + row * GridBlocks::gridColumns;
                m_map->addGrid(i, grid, GridBlocks::path);
                break;
            default:
                /**
                *   REVIEW:
                *   Ajoute un log error en cas d'erreur.
                *   les logs aide � la maintenance du projet sur le long terme
                *   Surtout pour les projets � plusieurs.
                */
                break;
        }
    }
}

void    Game::readGrid(std::string file)
{
    std::ifstream readFile;
    readFile.open(file, std::ios::in);
    
    if( readFile.is_open())
    {
        std::string line;
        int row = 0;
        while (std::getline(readFile, line))
        {
            addToMap(line, row);
            ++row;
        }
        readFile.close();
    }
    else
    {
        /**
        *   REVIEW:
        *   Tr�s bon log d'error!
        *   Besoin de la meme chose pour ligne 63
        */
        std::cerr << "Unable to open file" << std::endl;
    }
}

void    Game::readWaves(std::string file)
{
    std::ifstream readFile;
    readFile.open(file, std::ios::in);

    if (readFile.is_open())
    {
        std::string line;
        std::string str = "";
        int row = 0;
        while (std::getline(readFile, line))
        {
            for (int i = 0; i < line.length(); ++i)
            {
                char c = line[i];
                if (c == ']')
                {
                    m_waveManager->addWave(str);
                    str = "";
                }
                else if (c != ' ' && c != '[' )
                    str += c;
            }
        }
        readFile.close();
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl;
    }
}

void    Game::setPositions()
{
    m_world->setCastlePos(m_endIndex);
}

void    Game::draw(GPLib* gp)
{
    m_map->draw(gp);

    /**
    *   REVIEW:
    *   Regroupe toutes ces fonctions dans une seule!
    *   m_world->draw(gp);
    */
    m_world->drawCastle();
    m_world->drawTowers(gp);
    m_world->drawEnemies(gp);
    m_world->drawProjectiles(gp);
}

void    Game::drawStore(GPLib* gp)
{
    gpDrawRectFilled(gp, m_store->getRect(), m_store->getColor());
    m_world->drawTowersStore(gp, m_store->getStandardTowerPos(), m_store->getSlowingTowerPos(), m_store->getExplosiveTowerPos());
}

/**
*   REVIEW: Indentation peu habituelle. Standard:
* 
*   void Game::update(float elapsedTime, bool mouse1Pressed, bool mouse2Pressed,
*       GPVector2 mousePos, bool spacePressed, bool mouse1Released)
*/
void    Game::update
        (
            float elapsedTime, bool mouse1Pressed, bool mouse2Pressed,
            GPVector2 mousePos, bool spacePressed, bool mouse1Released
        )
{
    /**
    *   REVIEW:
    *   Split en plusieurs fonctions Update().
    *   UpdateMouse();
    *   m_waveManager->Update();
    *   ...
    */

    // adding towers
    if (mouse1Pressed)
    {
        // Grid* gridElement = map->getTowerGridElement(mousePos);
        // if (gridElement != nullptr && gridElement->isEmpty())
        // {
        //     int cost = world->addTower(gridElement->getPosition().m_x + GridBlocks::gridStep, 
        //     gridElement->getPosition().m_y + GridBlocks::gridStep, player->getMoney());
        //     gridElement->changeGridState();
        //     player->updateMoney(player->getMoney() - cost);
        // }
        // else if (gridElement != nullptr && !gridElement->isEmpty())
        // {
        // }
        Vector2f v_mousePos = { mousePos.x, mousePos.y };
        int mouseIndex = Math::getIndex(v_mousePos);
        if (mouseIndex == Math::getIndex(m_store->getStandardTowerPos()))
        {
            m_mouseCompanion.name = m_store->getStandardName();
            m_mouseCompanion.color = m_store->getStandardColor();
            m_mouseCompanion.radius = m_store->getStandardRadius();
            m_world->drawInactiveTower(v_mousePos, m_mouseCompanion.radius, m_mouseCompanion.color);
        }
        else if (mouseIndex == Math::getIndex(m_store->getSlowingTowerPos()))
        {
            m_mouseCompanion.name = m_store->getSlowingName();
            m_mouseCompanion.color = m_store->getSlowingColor();
            m_mouseCompanion.radius = m_store->getSlowingRadius();
            m_world->drawInactiveTower(v_mousePos, m_mouseCompanion.radius, m_mouseCompanion.color);
        }
        else if (mouseIndex == Math::getIndex(m_store->getExplosiveTowerPos()))
        {
            m_mouseCompanion.name = m_store->getExplosiveName();
            m_mouseCompanion.color = m_store->getExplosiveColor();
            m_mouseCompanion.radius = m_store->getExplosiveRadius();
            m_world->drawInactiveTower(v_mousePos, m_mouseCompanion.radius, m_mouseCompanion.color);
        }
    }
    else if (!mouse1Released && m_mouseCompanion.radius > 0.f)
    {
        Vector2f v_mousePos = { mousePos.x, mousePos.y };
        m_world->drawInactiveTower(v_mousePos, m_mouseCompanion.radius, m_mouseCompanion.color);
    }
    else if(mouse1Released)
    {
        /**
        *   REVIEW:
        *   Garde le pointer en cache au lieu de call 2 fois m_map->getTowerGridElement(mousePos).
        *   La fonction getTowerGridElement parse tous les elements de la grid, c'est couteux!
        * 
        *   Grid* grid = m_map->getTowerGridElement(mousePos);
        *   if(grid != nullptr)
        *   {
        *       Vector2f coord = grid->getPosition();
        *       // code...
        *   }
        */
        if (m_map->getTowerGridElement(mousePos) != nullptr)
        {
            Vector2f coord = m_map->getTowerGridElement(mousePos)->getPosition();
            m_player->updateMoney
                (
                    m_world->addTower(coord.m_x, coord.m_y, m_player->getMoney(), 
                    m_mouseCompanion.name, m_store->getPrice(m_mouseCompanion.name))
                );
        }
        m_mouseCompanion.name = "";
        m_mouseCompanion.radius = 0.f;
        m_mouseCompanion.color = { 0.f, 0.f, 0.f, 0.f };
            
    }

    // if (m_world->isDeserted())
    // {
    //     if(m_waveManager->getPauseTimer() > 0.f)
    //     {
    //         m_waveManager->updatePauseTimer(elapsedTime);
    //     }
    //     else
    //     {
           
    //     }
    // }

    if (m_waveManager->getWaveNum() < m_waveManager->getTotalWaves() && m_waveManager->getPauseTimer() <= 0.f)
    {
        m_waveManager->updateEnemyTimer(elapsedTime);
        bool spawnedEntireWave = m_world->spawnWave(m_waveManager->getCurrentWave(), m_startIndex, m_waveManager->getEnemyTimer());
        if (spawnedEntireWave)
            m_waveManager->resetPauseTimer();
        else if (m_waveManager->getEnemyTimer() <= 0.f)
        {
            m_waveManager->resetEnemyTimer();
            m_waveManager->stayOnWave();
        }
        else
            m_waveManager->stayOnWave();
    }
    else if (m_world->isDeserted())
    {
        m_waveManager->updatePauseTimer(elapsedTime);
    }
    
    
    /**
    *   REVIEW:
    *   Regroup methods!
    *   m_world->Update(elapsedTime)
    *   m_player->Update()
    */
    m_world->moveEnemies(elapsedTime, m_mapChars, m_endIndex);
    m_world->moveProjectiles(elapsedTime);
    m_world->checkTowerEnemyCollisions();
    m_world->checkProjectileEnemyCollisions(elapsedTime);
    m_world->shootEnemies(elapsedTime);
    m_world->healEnemies(elapsedTime);
    Vector2f playerUpdate = m_world->destroyDead();
    m_world->destroyFinished();
    m_player->updateMoney(m_player->getMoney() + playerUpdate.m_y);
    m_player->updateScore(m_player->getScore() + playerUpdate.m_x);
}