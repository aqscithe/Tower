#pragma once

#include <string>
#include <fstream>
#include <chrono>

#include "gp/gp.h"
#include "Map.h"
#include "World.h"
#include "Store.h"
#include "Player.h"
#include "WaveManager.h"

class Game
{
    private:
        Map*            m_map;
        World*          m_world;
        Store*          m_store;
        Player*         m_player;
        WaveManager*    m_waveManager;
        std::string     m_mapChars = "";
        int             m_startIndex = 0;
        int             m_endIndex = 0;

        struct          m_mouseCompanion
        {
            std::string name;
            float       radius;
            GPColor     color;
        } m_mouseCompanion;


    public:
        Game(GPLib* gp);
        ~Game();

        void    readGrid(std::string file);
        void    readWaves(std::string file);

        void    setPositions();

        void    addToMap(std::string line, int row);
        void    addWaveToManager(std::string line);
        
        void    draw(GPLib* gp);
        void    drawStore(GPLib* gp);

        void    update(float, bool, bool, GPVector2, bool, bool);

        std::string     getMapChars();
        
};