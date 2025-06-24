#include "GlassBrick.h"

namespace ArkanoidGame
{
    GlassBrick::GlassBrick(const sf::Vector2f& position, const sf::Vector2f& size)
        : Brick(position, size, sf::Color::Transparent, sf::Color::White, 2.f)
    {
        SetScoreStrategy(std::make_shared<GlassBrickScore>());
    }

    bool GlassBrick::OnHit()
    {
        destroyed = true;
        return false;
    }

    std::shared_ptr<Brick> GlassBrick::Clone() const
    {
        return std::make_shared<GlassBrick>(*this);
    }
}
