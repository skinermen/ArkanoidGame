#pragma once
#include "Bonus.h"
#include "../BallStrategies.h"

namespace ArkanoidGame
{
    class Platform;
    class FireBallBonus : public Bonus
    {
    public:
        explicit FireBallBonus(const sf::Vector2f& position);
        void Apply(Ball& ball, Platform& platform) override;
    };
}