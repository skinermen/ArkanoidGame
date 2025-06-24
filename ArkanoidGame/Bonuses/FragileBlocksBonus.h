#pragma once
#include "Bonus.h"
#include "../BallStrategies.h"

namespace ArkanoidGame
{
    class BrickManager;
    class Platform;

    class FragileBlocksBonus : public Bonus
    {
    public:
        FragileBlocksBonus(const sf::Vector2f& position, BrickManager& manager);
        void Apply(Ball& ball, Platform& platform) override;
    private:
        BrickManager& brickManager;
    };
}