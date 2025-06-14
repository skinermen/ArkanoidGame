#include "RecordManager.h"

#include <fstream>

namespace ArkanoidGame
{
    bool RecordManager::IsNewRecord(int score)
    {
        Load();
        return records.size() < SETTINGS.SIZE_LEADERBOARD || score > records.back().score;
    }

    void RecordManager::SaveRecord(const std::string& name, int score)
    {
        records.push_back({name, score});
        std::sort(records.begin(), records.end(), [](const auto& a, const auto& b)
        {
            return b.score < a.score;
        });
        if (records.size() > SETTINGS.SIZE_LEADERBOARD)
            records.resize(SETTINGS.SIZE_LEADERBOARD);
        Save();
    }

    void RecordManager::Load()
    {
        records.clear();
        std::ifstream fin(SETTINGS.LEADERBOARD_FILENAME);
        if (!fin.is_open()) return;

        std::string name;
        int score;
        while (fin >> name >> score)
        {
            records.push_back({name, score});
        }
    }
    void RecordManager::Save() const
    {
        std::ofstream fout(SETTINGS.LEADERBOARD_FILENAME);
        if (!fout.is_open()) return;

        for (const auto& r : records)
        {
            fout << r.playerName << ' ' << r.score << '\n';
        }
    }
}
