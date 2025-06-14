#pragma once
#include <string>
#include "../Scores/RecordManager.h"
#include "../GameState.h"

namespace ArkanoidGame
{
    class IRecordSaveStrategy
    {
    public:
        virtual ~IRecordSaveStrategy() = default;
        virtual void Save(RecordManager& manager, int score) = 0;
    };
}