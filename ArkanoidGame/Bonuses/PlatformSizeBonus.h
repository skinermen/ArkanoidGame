#pragma once
#include "Bonus.h"
#include "../PlatformCommand.h"
#include <memory>

namespace ArkanoidGame
{
    class PlatformSizeBonus : public Bonus
    {
    public:
        PlatformSizeBonus(const sf::Vector2f& position, std::unique_ptr<PlatformCommand> command);
        void Apply(Ball& ball, Platform& platform) override;
    private:
        std::unique_ptr<PlatformCommand> command;
    };
}