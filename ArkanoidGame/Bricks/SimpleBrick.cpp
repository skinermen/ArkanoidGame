#include "SimpleBrick.h"

namespace ArkanoidGame
{
    SimpleBrick::SimpleBrick(const sf::Vector2f& position, const sf::Vector2f& size)
    : Brick(position, size, sf::Color::Green, sf::Color::Green, 2.f)
    {
        SetScoreStrategy(std::make_shared<SimpleBrickScore>());
    }

    bool SimpleBrick::OnHit()
    {
        destroyed = true;
        return true;
    }

    std::shared_ptr<Brick> SimpleBrick::Clone() const
    {
        return std::make_shared<SimpleBrick>(*this);
    }
}
