#pragma once
#include "../Scores/RecordManager.h"

namespace ArkanoidGame
{
    class IRecordSaveStrategy
    {
    public:
        virtual ~IRecordSaveStrategy() = default;
        virtual void Save(RecordManager& manager, int score) = 0;
    };
}