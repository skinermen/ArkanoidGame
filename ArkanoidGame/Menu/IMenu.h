#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
    enum class GameState;
    
    class IMenu
    {
    public:
        virtual ~IMenu() = default;
        virtual void Init(const sf::Font& font) = 0;
        virtual void Draw(sf::RenderWindow& window) = 0;
        
        virtual void MoveUp() = 0;
        virtual void MoveDown() = 0;
        virtual void ResetSelection() = 0;
        virtual unsigned int GetSelectedIndex() const = 0;

        virtual void OnConfirm() = 0;
    };
}