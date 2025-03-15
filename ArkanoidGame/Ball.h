#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ArkanoidGame
{
    class Ball
    {
    public:
        Ball();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window) const;
        void Reset();
        void SetPosition(float x, float y);
        const sf::Vector2f& GetPosition() const { return ballShape.getPosition(); }
        const sf::CircleShape& GetShape() const { return ballShape; }
        void SetVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }
        const sf::Vector2f& GetVelocity() const { return velocity; }
        bool CheckCollisionWithPlatform(const class Platform& platform) const;
        
    private:
        sf::CircleShape ballShape;
        sf::Vector2f velocity; // направление и скорость (в пикселях в секунду)
        float speed;          // базовая скорость шарика
    };
}
