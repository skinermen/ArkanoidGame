#pragma once
#include <SFML/Graphics.hpp>
#include "../GameObject.h"

namespace ArkanoidGame
{
    class Ball;
    class Platform;

    class Bonus : public GameObject
    {
    public:
        explicit Bonus(const sf::Vector2f& position);
        void Update(sf::RenderWindow& window, float deltaTime) override;
        void Draw(sf::RenderWindow& window) const override;
        void SetPosition(const sf::Vector2f& pos) override { shape.setPosition(pos); }
        sf::Vector2f GetPosition() const override { return shape.getPosition(); }
        bool IsCollected() const { return collected; }
        bool IsOffScreen() const;
        virtual void Apply(Ball& ball, Platform& platform) = 0;
        sf::FloatRect GetBounds() const { return shape.getGlobalBounds(); }
    protected:
        sf::RectangleShape shape;
        float fallSpeed = 100.f;
        bool collected = false;
    };
}