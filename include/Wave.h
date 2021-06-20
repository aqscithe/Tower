#pragma once

#include <string>

class Wave
{
    private:
        std::string m_waveChars = "";

    public:
        /**
        *   REVIEW:
        *   Utilise const std::string& pour eviter une copie.
        */
        Wave(std::string waveChars);
        ~Wave();

        /**
        *   REVIEW:
        *   Simplification public const std::string m_waveChars;
        */
        std::string     getWaveChars() const;

        /**
        *   REVIEW:
        *   Fonction non définie: supprime la declaration.
        */
        void            spawnWave();
};