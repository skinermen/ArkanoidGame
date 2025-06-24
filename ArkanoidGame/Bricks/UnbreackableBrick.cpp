#include "UnbreackableBrick.h"

namespace ArkanoidGame
{
    UnbreackableBrick::UnbreackableBrick(const sf::Vector2f& position, const sf::Vector2f& size)
        : Brick(position, size, sf::Color(100, 100, 100), sf::Color(100, 100, 100), 2.f)
    {
        SetScoreStrategy(std::make_shared<UnbreakableBrickScore>());
    }

    bool UnbreackableBrick::OnHit()
    {
        return true;
    }

    std::shared_ptr<Brick> UnbreackableBrick::Clone() const
    {
        return std::make_shared<UnbreackableBrick>(*this);
    }
}
