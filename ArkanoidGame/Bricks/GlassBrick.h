#pragma once
#include "Brick.h"

namespace ArkanoidGame
{
    class GlassBrick : public Brick
    {
    public:
        GlassBrick(const sf::Vector2f& position, const sf::Vector2f& size);
        bool OnHit() override;
        bool IsGlass() const { return true; }
        std::shared_ptr<Brick> Clone() const override;
    };
}
