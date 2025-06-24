#pragma once
#include "Brick.h"

namespace ArkanoidGame
{
    class SimpleBrick : public Brick
    {
    public:
        SimpleBrick(const sf::Vector2f& position, const sf::Vector2f& size);
        bool OnHit() override;
        std::shared_ptr<Brick> Clone() const override;
    };
}
