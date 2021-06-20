#include <iostream>

#include "WaveManager.h"

WaveManager::WaveManager()
{
    m_pauseInterval = 20.f;
    m_pauseTimer = m_pauseInterval;
    m_enemyInterval = 0.5f;
    m_enemyTimer = m_enemyInterval;
}

WaveManager::~WaveManager()
{}

void    WaveManager::addWave(std::string waveStr)
{
    this->m_wave.push_back(new Wave(waveStr));
    ++m_totalWaves;
}

int     WaveManager::getTotalWaves() const
{
    return m_totalWaves;
}
        
Wave*     WaveManager::getCurrentWave()
{
    int index = 0;
    for (Wave* element : m_wave)
    {
        if (index == m_waveNum)
        {
            ++m_waveNum;
            return element;
        } 
        ++index;
    }
    return nullptr;
}

int     WaveManager::getWaveNum() const
{
    return m_waveNum;
}

void    WaveManager::stayOnWave()
{
    --m_waveNum;
}

void    WaveManager::updatePauseTimer(float elapsedTime)
{
    m_pauseTimer -= elapsedTime;
}

float   WaveManager::getPauseInteveral() const
{
    return m_pauseInterval;
}

void    WaveManager::updateEnemyTimer(float elapsedTime)
{
    m_enemyTimer -= elapsedTime;
}

float   WaveManager::getPauseTimer() const
{
    return m_pauseTimer;
}

float   WaveManager::getEnemyTimer() const
{
    return m_enemyTimer;
}

void    WaveManager::resetPauseTimer()
{
    std::cout << "ON SE REPOSE JUSQU'À LA PROCHAINE VAGUE" << std::endl;
    m_pauseTimer = m_pauseInterval;
}

void    WaveManager::resetEnemyTimer()
{
    m_enemyTimer = m_enemyInterval;
}