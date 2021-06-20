#include <iostream>

#include "Player.h"

Player::~Player()
{
}

void    Player::updateMoney(int updatedMoney)
{
    if (updatedMoney != m_money)
    {
        m_money = updatedMoney;
        std::cout << "UPDATED MONEY " << m_money << std::endl;
    }
}

void    Player::updateScore(int newScore)
{
    if (newScore != m_score)
    {
        m_score = newScore;
        std::cout << "NEW SCORE " << m_score << std::endl;
    }
}

int     Player::getMoney() const
{
    return m_money;
}

int     Player::getScore() const
{
    return m_score;
}

Player& Player::operator=(const Player& player)
{
    this->m_money = player.m_money;
    this->m_score = player.m_score;
    return *this;
}