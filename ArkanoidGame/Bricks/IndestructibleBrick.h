#pragma once
#include "Brick.h"

namespace ArkanoidGame
{
    class IndestructibleBrick : public Brick
    {
    public:
        IndestructibleBrick(const sf::Vector2f& position, const sf::Vector2f& size);
        bool OnHit() override;
    };
}
