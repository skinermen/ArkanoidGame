#pragma once
#include "MenuBase.h"

namespace ArkanoidGame
{
    class GameOverMenu : public MenuBase
    {
    public:
        void Init(const sf::Font& font) override;
        void Draw(sf::RenderWindow& window) override;
        void OnConfirm() override;

        void SetScore(int score);
  
    private:
        sf::Text scoreTitle;
        sf::Text scoreValue;
        sf::Text recordsTitle;
        std::vector<sf::Text> leaderboardItems;
    };
}