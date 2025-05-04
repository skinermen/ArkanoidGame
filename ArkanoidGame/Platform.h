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
        
        const sf::RectangleShape& GetShape() const { return platformShape; }
        
    private:
        sf::RectangleShape platformShape;
        float speed = SETTINGS.SPEED_PLATFORM;
        bool useMouseControl = false;
        sf::Vector2f lastMousePosition;
        float mouseMoveThreshold = SETTINGS.MOUSE_MOVE_THRESHOLD;
    };
}
