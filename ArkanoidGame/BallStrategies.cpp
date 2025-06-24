#include "BallStrategies.h"
#include "Ball.h"
#include "Bricks/Brick.h"
#include "Bricks/UnbreackableBrick.h"

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
}