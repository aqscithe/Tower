#include "Wave.h"

Wave::Wave(std::string waveChars)
{
    this->m_waveChars = waveChars;
}

Wave::~Wave()
{}

std::string     Wave::getWaveChars() const
{
    return m_waveChars;
}