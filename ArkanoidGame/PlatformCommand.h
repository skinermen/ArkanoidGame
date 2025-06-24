#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
    class Platform;

    class PlatformCommand
    {
    public:
        virtual ~PlatformCommand() = default;
        virtual void Execute(Platform& platform) = 0;
    };

    class IncreaseSizeCommand : public PlatformCommand
    {
    public:
        IncreaseSizeCommand(float factor, float duration)
            : factor(factor), duration(duration) {}
        void Execute(Platform& platform) override;
    private:
        float factor;
        float duration;
    };

    class DecreaseSizeCommand : public PlatformCommand
    {
    public:
        DecreaseSizeCommand(float factor, float duration)
            : factor(factor), duration(duration) {}
        void Execute(Platform& platform) override;
    private:
        float factor;
        float duration;
    };
}