#pragma once
#include "MenuBase.h"

namespace ArkanoidGame
{
    class ConfirmationMenu : public MenuBase
    {
    public:
        enum class Choice { Yes = 0, No = 1 };
        
        void Init(const sf::Font& font) override;
        void Draw(sf::RenderWindow& window) override;
        void OnConfirm() override;
        Choice GetSelection() const;

    };
}