#pragma once

#include <string>

class Wave
{
    private:
        std::string m_waveChars = "";

    public:
        Wave(std::string waveChars);
        ~Wave();

        std::string     getWaveChars() const;

        void            spawnWave();
};