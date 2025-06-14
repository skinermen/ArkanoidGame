#pragma once

namespace ArkanoidGame
{
    // Strategy for calculating glasses for one block
    class IScoreStrategy
    {
    public:
        virtual ~IScoreStrategy() = default;
        virtual int GetScore() const = 0;
    };

}