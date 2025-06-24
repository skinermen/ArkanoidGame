#include "Brick.h"

namespace ArkanoidGame
{
    Brick::Brick(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color,
                 const sf::Color& outlineColor, const float outlineThickness)
    {
        brickShape.setSize(size);
        brickShape.setOrigin(size.x / 2.f, size.y / 2.f);
        brickShape.setPosition(position);
        brickShape.setFillColor(color);
        brickShape.setOutlineColor(outlineColor);
        brickShape.setOutlineThickness(outlineThickness);
        
    }

    void Brick::Update(sf::RenderWindow& window, float deltaTime)
    {
        
    }

    void Brick::Draw(sf::RenderWindow& window) const
    {
        if (!destroyed)
            window.draw(brickShape);
    }

    bool Brick::IsDestroyed() const { return destroyed; }

    sf::FloatRect Brick::GetBounds() const { return brickShape.getGlobalBounds(); }

    sf::Vector2f Brick::GetPosition() const { return brickShape.getPosition(); }

    void Brick::SetPosition(const sf::Vector2f& pos) { brickShape.setPosition(pos); }

    void Brick::Destroy() { destroyed = true; }

    void Brick::SetColor(const sf::Color& color)
    {
        brickShape.setFillColor(color);
        brickShape.setOutlineColor(color);
    }

    sf::Color Brick::GetColor() const
    {
        return brickShape.getFillColor();
    }
}
