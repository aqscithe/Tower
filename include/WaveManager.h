#pragma once

#include <vector>
#include <string>

#include "Wave.h"

class WaveManager
{
    private:
        std::vector<Wave*>  m_wave;
        float               m_pauseTimer = 0.f;
        float               m_pauseInterval = 0.f;
        float               m_enemyTimer = 0.f;
        float               m_enemyInterval = 0.f;
        int                 m_waveNum = 0;
        int                 m_totalWaves = 0;

    public:
        WaveManager();
        ~WaveManager();

        /**
        *   REVIEW: Utilise const std::string& pour eviter une copie.
        */
        void    addWave(std::string waveStr);

        int     getTotalWaves() const;
        Wave*   getCurrentWave();
        int     getWaveNum() const;
        void    stayOnWave();
        float   getPauseTimer() const;
        float   getPauseInteveral() const;
        void    updatePauseTimer(float elapsedTime);
        void    updateEnemyTimer(float elapsedTime);
        float   getEnemyTimer() const;
        float   getEnemyInterval() const;
        void    resetPauseTimer();
        void    resetEnemyTimer();
};