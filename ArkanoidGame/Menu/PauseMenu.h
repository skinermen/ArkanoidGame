#pragma once
#include "MenuBase.h"

namespace ArkanoidGame
{
    class PauseMenu : public MenuBase
    {
    public:
        void Init(const sf::Font& font) override;
        void Draw(sf::RenderWindow& window) override;
        void OnConfirm() override;
    };
}