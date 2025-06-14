#pragma once
#include "MenuBase.h"
#include "LeaderboardMenu.h"

namespace ArkanoidGame
{
    class GameOverMenu : public MenuBase
    {
    public:
        void Init(const sf::Font& font) override;
        void Draw(sf::RenderWindow& window) override;
        void OnConfirm() override;

        void UpdateRecords(const std::vector<SLeaderboard>& newRecords, const sf::Font& font);

        void SetScore(int score);
  
    private:
        sf::Text scoreTitle;
        sf::Text scoreValue;
        sf::Text recordsTitle;
        sf::Text combinedTextScores;
        std::vector<sf::Text> leaderboardItems;
        std::vector<SLeaderboard> records;
    };
}