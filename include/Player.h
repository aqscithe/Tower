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

        /**
        *   REVIEW:
        *   get(){retrun x} + set(newX){x = newX} est la meme chose qu'une variable en public!
        *   Simplifie la syntaxe.
        */
        int     getMoney() const;
        int     getScore() const;

        void    updateMoney(int updatedMoney);
        void    updateScore(int newScore);

        Player& operator=(const Player& player);
};