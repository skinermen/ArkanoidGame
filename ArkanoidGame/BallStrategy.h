#pragma once

namespace ArkanoidGame
{
    class Ball;
    class Brick;

    class BallStrategy
    {
    public:
        virtual ~BallStrategy() = default;
        virtual void OnEnter(Ball& ball) {}
        virtual void OnExit(Ball& ball) {}
        virtual void Update(Ball& ball, float deltaTime) {}
        // returns true if ball should bounce from brick
        virtual bool OnBrickHit(Ball& ball, Brick& brick) = 0;
        virtual bool IsFinished() const { return false; }
    };
}