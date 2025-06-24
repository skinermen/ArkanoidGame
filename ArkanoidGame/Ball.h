#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Settings.h"
#include "GameObject.h"
#include "BallStrategy.h"

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
        sf::CircleShape& GetShape() { return ballShape; }
        void SetColor(const sf::Color& color) { ballShape.setFillColor(color); }
        sf::Color GetColor() const { return ballShape.getFillColor(); }
        void SetVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }
        const sf::Vector2f& GetVelocity() const { return velocity; }
        void SetStrategy(std::unique_ptr<BallStrategy> newStrategy);
        BallStrategy* GetStrategy() const { return strategy.get(); }
        bool CheckCollisionWithPlatform(const class Platform& platform) const;
        bool CheckCollisionWithBrick(const class Brick& brick) const;
        int CollisionHandlingWithObjects(const Platform& platform, const std::vector<std::shared_ptr<Brick>>& bricks);
        
    private:
        sf::CircleShape ballShape;
        sf::Vector2f velocity = SETTINGS.INITIAL_DIRECTION_OF_THE_BALL; // Direction and speed (in pixels per second)
        float speed = SETTINGS.SPEED_BALL;          // The basic speed of the ball
        std::unique_ptr<BallStrategy> strategy;
    };
}
