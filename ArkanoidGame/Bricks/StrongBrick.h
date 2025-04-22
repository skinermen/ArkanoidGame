#pragma once
#include "Brick.h"

namespace ArkanoidGame
{
    class StrongBrick : public Brick
    {
    public:
        StrongBrick(const sf::Vector2f& position, const sf::Vector2f& size);
        bool OnHit() override;

    private:
        int hitPoints = 3;
    };
}
