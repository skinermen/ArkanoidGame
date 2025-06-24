#include "FireBallBonus.h"
#include "../Ball.h"

#include <memory>

namespace ArkanoidGame
{

    FireBallBonus::FireBallBonus(const sf::Vector2f& position)
        : Bonus(position)
    {
        shape.setFillColor(sf::Color::Red);
    }

    void FireBallBonus::Apply(Ball& ball, Platform& /*platform*/)
    {
        ball.SetStrategy(std::make_unique<FireBallStrategy>(7.f));
        collected = true;
    }
}