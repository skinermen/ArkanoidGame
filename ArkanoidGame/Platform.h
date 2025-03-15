#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ArkanoidGame
{
    class Platform
    {
    public:
        Platform();
        
        void Update(const sf::RenderWindow& window, float deltaTime);
        void Draw(sf::RenderWindow& window) const;
        void SetPosition(float x, float y);

        const sf::RectangleShape& GetShape() const { return platformShape; }

    private:
        sf::RectangleShape platformShape;
        float speed = SPEED_PLATFORM;
        
        bool useMouseControl = false; // True - mouse, false - keyboard
        sf::Vector2f lastMousePosition;
        float mouseMoveThreshold = MOUSE_MOVE_THRESHOLD;
    };
}
