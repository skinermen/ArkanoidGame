#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArkanoidGame
{
    class Brick : public GameObject
    {
    public:
        Brick(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
        ~Brick() override = default;
        
        void Update(sf::RenderWindow& window, float deltaTime) override;
        void Draw(sf::RenderWindow& window) const override;
        void SetPosition(const sf::Vector2f& pos) override;
        sf::Vector2f GetPosition() const override;
        
        sf::FloatRect GetBounds() const;
        
        void Destroy();
        bool IsDestroyed() const;

    private:
        sf::RectangleShape brickShape;
        bool destroyed;
    };
}
