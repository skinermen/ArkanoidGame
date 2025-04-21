#include "Brick.h"

namespace ArkanoidGame
{
    Brick::Brick(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
        : destroyed(false)
    {
        brickShape.setSize(size);
        brickShape.setFillColor(color);
        brickShape.setOrigin(size.x / 2.f, size.y / 2.f);
        brickShape.setPosition(position);
    }

    void Brick::Update(sf::RenderWindow& window, float deltaTime)
    {
        
    }

    void Brick::Draw(sf::RenderWindow& window) const
    {
        if (!destroyed)
            window.draw(brickShape);
    }

    void Brick::SetPosition(const sf::Vector2f& pos)
    {
        brickShape.setPosition(pos);
    }

    sf::Vector2f Brick::GetPosition() const
    {
        return brickShape.getPosition();
    }

    sf::FloatRect Brick::GetBounds() const
    {
        return brickShape.getGlobalBounds();
    }

    void Brick::Destroy()
    {
        destroyed = true;
    }

    bool Brick::IsDestroyed() const
    {
        return destroyed;
    }
}
