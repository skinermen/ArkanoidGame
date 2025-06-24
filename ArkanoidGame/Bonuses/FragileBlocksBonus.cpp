#include <memory>

#include "FragileBlocksBonus.h"
#include "../Ball.h"
#include "../Bricks/BrickManager.h"

namespace ArkanoidGame
{
    FragileBlocksBonus::FragileBlocksBonus(const sf::Vector2f& position, BrickManager& manager)
        : Bonus(position), brickManager(manager)
    {
        shape.setFillColor(sf::Color::Cyan);
    }

    void FragileBlocksBonus::Apply(Ball& ball, Platform& /*platform*/)
    {
        ball.SetStrategy(std::make_unique<FragileBallStrategy>(brickManager, 7.f));
        collected = true;
    }
}