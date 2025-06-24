#pragma once
#include "MenuBase.h"
#include <functional>

namespace ArkanoidGame
{
    class WinnerMenu : public MenuBase
    {
    public:
        void Init(const sf::Font& font) override;
        void Draw(sf::RenderWindow& window) override;
        void OnConfirm() override;
        
        void SetOnConfirmCallback(std::function<void(int)> cb);
        void SetScore(int score);

    private:
        sf::Text scoreTitle;
        sf::Text scoreValue;
        sf::Text combinedTextScores;
        std::function<void(int)> onConfirmCallback;
    };
}