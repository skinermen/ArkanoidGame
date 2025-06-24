#include "PlatformSizeBonus.h"
#include "../Platform.h"

namespace ArkanoidGame
{
    PlatformSizeBonus::PlatformSizeBonus(const sf::Vector2f& position, std::unique_ptr<PlatformCommand> cmd)
    : Bonus(position), command(std::move(cmd))
    {
        shape.setFillColor(sf::Color::Green);
    }

    void PlatformSizeBonus::Apply(Ball& /*ball*/, Platform& platform)
    {
        if (command)
            command->Execute(platform);
        collected = true;
    }
}