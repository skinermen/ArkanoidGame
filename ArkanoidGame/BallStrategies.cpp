#include "BallStrategies.h"
#include "Ball.h"
#include "Bricks/Brick.h"
#include "Bricks/UnbreackableBrick.h"
#include "Bricks/BrickManager.h"

namespace ArkanoidGame
{

    bool NormalBallStrategy::OnBrickHit(Ball& ball, Brick& brick)
    {
        return brick.OnHit();
    }

    void FireBallStrategy::OnEnter(Ball& ball)
    {
        prevColor = ball.GetColor();
        speedMultiplier = 1.2f;
        sf::Vector2f vel = ball.GetVelocity();
        vel.x *= speedMultiplier;
        vel.y *= speedMultiplier;
        ball.SetVelocity(vel);
        ball.SetColor(sf::Color::Red);
    }

    void FireBallStrategy::OnExit(Ball& ball)
    {
        sf::Vector2f vel = ball.GetVelocity();
        vel.x /= speedMultiplier;
        vel.y /= speedMultiplier;
        ball.SetVelocity(vel);
        ball.SetColor(prevColor);
    }

    void FireBallStrategy::Update(Ball& ball, float deltaTime)
    {
        remainingTime -= deltaTime;
    }

    bool FireBallStrategy::OnBrickHit(Ball& ball, Brick& brick)
    {
        brick.OnHit();
        if (auto* unb = dynamic_cast<UnbreackableBrick*>(&brick))
            unb->Destroy();
        return false; // no bounce
    }

    FragileBallStrategy::FragileBallStrategy(BrickManager& manager, float duration)
        : brickManager(manager), remainingTime(duration) {}

    void FragileBallStrategy::OnEnter(Ball& /*ball*/)
    {
        originalColors.clear();
        const auto& bricks = brickManager.GetBricks();
        originalColors.reserve(bricks.size());
        for (const auto& b : bricks)
        {
            originalColors.push_back(b->GetColor());
            if (!dynamic_cast<UnbreackableBrick*>(b.get()))
            {
                b->SetColor(sf::Color::Cyan);
            }
        }
    }

    void FragileBallStrategy::OnExit(Ball& /*ball*/)
    {
        const auto& bricks = brickManager.GetBricks();
        for (std::size_t i = 0; i < bricks.size() && i < originalColors.size(); ++i)
        {
            bricks[i]->SetColor(originalColors[i]);
        }
    }

    void FragileBallStrategy::Update(Ball& ball, float deltaTime)
    {
        remainingTime -= deltaTime;
    }

    bool FragileBallStrategy::OnBrickHit(Ball& ball, Brick& brick)
    {
        if (dynamic_cast<UnbreackableBrick*>(&brick))
        {
            return brick.OnHit();
        }
        brick.Destroy();
        return true; // bounce
    }
}