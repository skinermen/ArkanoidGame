#pragma once
#include "MenuBase.h"

namespace ArkanoidGame
{
    class NameInputMenu : public MenuBase
    {
    public:
        void Init(const sf::Font& font) override;
        void Draw(sf::RenderWindow& window) override;
        void OnConfirm() override;

        // Management of the introduced name
        void AppendChar(char c);
        void RemoveLastChar();
        void Reset();
        
        const std::string& GetPlayerName() const;

    private:
        std::string playerName;
        sf::Text nameText;
    };
}