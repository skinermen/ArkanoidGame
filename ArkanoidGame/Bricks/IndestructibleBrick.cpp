#include "IndestructibleBrick.h"

namespace ArkanoidGame
{
    IndestructibleBrick::IndestructibleBrick(const sf::Vector2f& position, const sf::Vector2f& size)
        : Brick(position, size, sf::Color(100, 100, 100), sf::Color(100, 100, 100), 2.f) {}

    bool IndestructibleBrick::OnHit()
    {
        return true;
    }
}
