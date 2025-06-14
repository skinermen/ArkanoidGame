#pragma once
#include "IScoreStrategy.h"

namespace ArkanoidGame
{
    class SimpleBrickScore : public IScoreStrategy
    {
    public:
        int GetScore() const override { return 10; }
    };

    class StrongBrickScore : public IScoreStrategy
    {
    public:
        int GetScore() const override { return 20; }
    };

    class GlassBrickScore : public IScoreStrategy
    {
    public:
        int GetScore() const override { return 15; }
    };

    class UnbreakableBrickScore : public IScoreStrategy
    {
    public:
        int GetScore() const override { return 0; }
    };
}