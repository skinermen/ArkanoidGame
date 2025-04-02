#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "GameObject.h"

namespace ArkanoidGame
{
    class Ball : public GameObject
    {
    public:
        Ball();
        void Update(sf::RenderWindow& window, float deltaTime) override;
        void Draw(sf::RenderWindow& window) const override;
        void SetPosition(const sf::Vector2f& pos) override;
        sf::Vector2f GetPosition() const override;
        
        void Reset();
        const sf::CircleShape& GetShape() const { return ballShape; }
        void SetVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }
        const sf::Vector2f& GetVelocity() const { return velocity; }
        bool CheckCollisionWithPlatform(const class Platform& platform) const;
        bool CheckCollisionWithBrick(const class Brick& brick) const;
        
    private:
        sf::CircleShape ballShape;
        sf::Vector2f velocity = INITIAL_DIRECTION_OF_THE_BALL; // Direction and speed (in pixels per second)
        float speed = SPEED_BALL;          // The basic speed of the ball
    };
}
