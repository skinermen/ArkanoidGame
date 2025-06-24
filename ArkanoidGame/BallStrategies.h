#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "BallStrategy.h"
#include "Settings.h"

namespace ArkanoidGame
{

    class NormalBallStrategy : public BallStrategy
    {
    public:
        bool OnBrickHit(Ball& ball, Brick& brick) override;
    };

    class FireBallStrategy : public BallStrategy
    {
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

    class BrickManager;

    class FragileBallStrategy : public BallStrategy
    {
    public:
        FragileBallStrategy(BrickManager& manager, float duration = 5.f);
        void OnEnter(Ball& ball) override;
        void OnExit(Ball& ball) override;
        void Update(Ball& ball, float deltaTime) override;
        bool OnBrickHit(Ball& ball, Brick& brick) override;
        bool IsFinished() const override { return remainingTime <= 0.f; }
    private:
        BrickManager& brickManager;
        float remainingTime;
        std::vector<sf::Color> originalColors;
    };
}