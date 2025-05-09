﻿#pragma once
#include <SFML/Graphics.hpp>
#include "../GameObject.h"

namespace ArkanoidGame
{
    class Brick : public GameObject
    {
    public:
        Brick(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color,
              const sf::Color& outlineColor, const float outlineThickness);
        ~Brick() override = default;

        virtual void Update(sf::RenderWindow& window, float deltaTime) override;
        virtual void Draw(sf::RenderWindow& window) const override;
        virtual sf::Vector2f GetPosition() const override;
        virtual void SetPosition(const sf::Vector2f& pos) override;

        virtual bool OnHit() = 0;
        virtual bool IsDestroyed() const;
        virtual sf::FloatRect GetBounds() const;

    protected:
        sf::RectangleShape brickShape;
        bool destroyed = false;
    };
}
