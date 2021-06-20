#pragma once

class Player
{
    private:
        int     m_money = 0;
        int     m_score = 0;

    public:
        Player(int money, int score)
        : m_money(money), m_score(score)
        {}

        Player(const Player& player)
        {
            this->m_money = player.m_money;
            this->m_score = player.m_score;
        }

        ~Player();

        int     getMoney() const;
        int     getScore() const;

        void    updateMoney(int updatedMoney);
        void    updateScore(int newScore);

        Player& operator=(const Player& player);
};