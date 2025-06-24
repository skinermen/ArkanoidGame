#include "PlatformCommand.h"
#include "Platform.h"

namespace ArkanoidGame
{

    void IncreaseSizeCommand::Execute(Platform& platform)
    {
        platform.ApplySizeBonus(factor, duration);
    }

    void DecreaseSizeCommand::Execute(Platform& platform)
    {
        platform.ApplySizeBonus(factor, duration);
    }

}