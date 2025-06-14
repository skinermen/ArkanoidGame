#pragma once
#include "IRecordSaveStrategy.h"

namespace ArkanoidGame
{
    class RecordSaveWithDefaultName : public IRecordSaveStrategy
    {
    public:
        void Save(RecordManager& manager, int score) override
        {
            manager.SaveRecord("XYZ", score);
        }
    };
}