#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "GameObject.h"

namespace ArkanoidGame
{
    class Platform : public GameObject
    {
    public:
        Platform();
        
        void Update(sf::RenderWindow& window, float deltaTime) override;
        void Draw(sf::RenderWindow& window) const override;
        void SetPosition(const sf::Vector2f& pos) override;
        sf::Vector2f GetPosition() const override;
        void SetSize(const sf::Vector2f& size);
        sf::Vector2f GetSize() const { return platformShape.getSize(); }
        void ApplySizeBonus(float factor, float duration);
        void ResetSize();
        
        const sf::RectangleShape& GetShape() const { return platformShape; }
        
    private:
        sf::RectangleShape platformShape;
        float speed = SETTINGS.SPEED_PLATFORM;
        bool useMouseControl = false;
        sf::Vector2f lastMousePosition;
        float mouseMoveThreshold = SETTINGS.MOUSE_MOVE_THRESHOLD;
        sf::Vector2f defaultSize;
        float bonusTimer = 0.f;
        bool sizeModified = false;
    };
}
