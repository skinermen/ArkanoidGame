#include "Bonus.h"
#include "../Settings.h"

namespace ArkanoidGame
{
    Bonus::Bonus(const sf::Vector2f& position)
    {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setOrigin(shape.getSize() / 2.f);
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
        return shape.getPosition().y - shape.getSize().y / 2.f > SETTINGS.SCREEN_HEIGHT;
    }
}