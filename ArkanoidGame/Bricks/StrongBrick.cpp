#include "StrongBrick.h"

namespace ArkanoidGame
{
    StrongBrick::StrongBrick(const sf::Vector2f& position, const sf::Vector2f& size)
        : Brick(position, size, sf::Color::Blue, sf::Color::Blue, 2.f)
    {
        SetScoreStrategy(std::make_shared<StrongBrickScore>());
    }

    bool StrongBrick::OnHit()
    {
        if (hitPoints > 1)
        {
            --hitPoints;
            if (hitPoints == 2)
            {
                brickShape.setFillColor(sf::Color::Yellow);
                brickShape.setOutlineColor(sf::Color::Yellow);
            }
                
            else if (hitPoints == 1)
            {
                brickShape.setFillColor(sf::Color::Red);
                brickShape.setOutlineColor(sf::Color::Red);
            }
            return true;
        }
        else
        {
            destroyed = true;
            return true;
        }
    }

    std::shared_ptr<Brick> StrongBrick::Clone() const
    {
        return std::make_shared<StrongBrick>(*this);
    }
}
