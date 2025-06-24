#pragma once

namespace ArkanoidGame
{
    class IScoreStrategy
    {
    public:
        virtual ~IScoreStrategy() = default;
        virtual int GetScore() const = 0;
    };

}