#pragma once
#include "BallStrategy.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{

    class NormalBallStrategy : public BallStrategy
    {
    public:
        bool OnBrickHit(Ball& ball, Brick& brick) override;
    };

    class FireBallStrategy : public BallStrategy {
    public:
        explicit FireBallStrategy(float duration = 5.f) : remainingTime(duration) {}
        void OnEnter(Ball& ball) override;
        void OnExit(Ball& ball) override;
        void Update(Ball& ball, float deltaTime) override;
        bool OnBrickHit(Ball& ball, Brick& brick) override;
        bool IsFinished() const override { return remainingTime <= 0.f; }
    private:
        float remainingTime;
        sf::Color prevColor;
        float speedMultiplier = 1.0f;
    };
}