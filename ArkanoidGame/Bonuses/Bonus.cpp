#include "Bonus.h"
#include "../Settings.h"

namespace ArkanoidGame
{
    Bonus::Bonus(const sf::Vector2f& position)
    {
        shape.setRadius(10.f);
        shape.setOrigin(shape.getRadius(), shape.getRadius());
        shape.setFillColor(sf::Color::White);
        shape.setPosition(position);
    }

    void Bonus::Update(sf::RenderWindow& window, float deltaTime)
    {
        shape.move(0.f, fallSpeed * deltaTime);
    }

    void Bonus::Draw(sf::RenderWindow& window) const
    {
        window.draw(shape);
    }

    bool Bonus::IsOffScreen() const
    {
        return shape.getPosition().y - shape.getRadius() > SETTINGS.SCREEN_HEIGHT;
    }
}