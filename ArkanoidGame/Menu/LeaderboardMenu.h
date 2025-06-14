#pragma once
#include <vector>
#include <string>

#include "MenuBase.h"
#include "../Settings.h"

namespace ArkanoidGame
{
    struct SLeaderboard
    {
        std::string playerName;
        int score;
    };

    class LeaderboardMenu : public MenuBase
    {
    public:
        void Init(const sf::Font& font) override;
        void Draw(sf::RenderWindow& window) override;
        void OnConfirm() override;
        void ResetSelection() override;
        
        void LoadRecordsFromFile(const std::string& filename);
        void SaveRecordsToFile(const std::string& filename) const;
        void AddRecord(const std::string& filename, const std::string& playerName, int score);

        const std::vector<SLeaderboard>& GetRecords() const { return records; }

    private:
        sf::Text instructionsText;
        std::vector<SLeaderboard> records;
    };
}