#pragma once
#include "IRecordSaveStrategy.h"
#include "../Menu/NameInputMenu.h"
#include "../UI.h"

namespace ArkanoidGame
{
    class RecordSaveWithInputName : public IRecordSaveStrategy
    {
    public:
        RecordSaveWithInputName(UI& ui) : ui(ui) {}
        void Save(RecordManager& manager, int score) override
        {
            auto it = ui.GetMenu(GameState::NameInputMenu);
            if (auto* nameMenu = dynamic_cast<NameInputMenu*>(it))
            {
                std::string name = nameMenu->GetPlayerName();
                if (name.empty()) name = "XYZ";
                manager.SaveRecord(name, score);
            }
        }

    private:
        UI& ui;
    };
}