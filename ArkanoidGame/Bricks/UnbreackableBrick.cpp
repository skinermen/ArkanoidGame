#include "UnbreackableBrick.h"

namespace ArkanoidGame
{
    UnbreackableBrick::UnbreackableBrick(const sf::Vector2f& position, const sf::Vector2f& size)
        : Brick(position, size, sf::Color(100, 100, 100), sf::Color(100, 100, 100), 2.f) {}

    bool UnbreackableBrick::OnHit()
    {
        return true;
    }
}
