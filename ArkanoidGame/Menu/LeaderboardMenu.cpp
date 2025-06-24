#include <fstream>

#include "LeaderboardMenu.h"

namespace ArkanoidGame
{

    void LeaderboardMenu::Init(const sf::Font& font)
        {
        InitCommon(font, "Scoreboard:", {}, 48.f, 38.f);

        instructionsText.setFont(font);
        instructionsText.setCharacterSize(24);
        instructionsText.setFillColor(sf::Color::White);
        instructionsText.setString("Press B to return to the main menu");
        instructionsText.setOrigin(
            instructionsText.getLocalBounds().width / 2.f,
            instructionsText.getLocalBounds().height
        );

        // We load the records
        records.clear();
        LoadRecordsFromFile(SETTINGS.LEADERBOARD_FILENAME);

        // We form the texts of the points
        items.clear();
        for (size_t i = 0; i < records.size(); ++i)
        {
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(38);
            t.setFillColor(sf::Color::White);
            t.setString
            (
                std::to_string(i + 1) + ". " + records[i].playerName +
                " - " + std::to_string(records[i].score)
            );
            items.push_back(t);
        }
    }

    void LeaderboardMenu::Draw(sf::RenderWindow& window)
    {
        background.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            SETTINGS.SCREEN_HEIGHT / 2.f
        );
        window.draw(background);

        title.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            title.getLocalBounds().height
        );
        window.draw(title);

        instructionsText.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            SETTINGS.SCREEN_HEIGHT - 50.f
        );
        window.draw(instructionsText);

        DrawItems(window, items, SETTINGS.SCREEN_WIDTH / 2.f, 90.f, 40.f );
    }

    void LeaderboardMenu::OnConfirm(){}

    void LeaderboardMenu::ResetSelection()
    {
        for (auto& t : items)
            t.setFillColor(sf::Color::White);
    }

    void LeaderboardMenu::LoadRecordsFromFile(const std::string& filename)
    {
        records.clear();
        std::ifstream fin(filename);
        if (!fin.is_open()) return;
        std::string name;
        int score;
        while (fin >> name >> score)
        {
            records.push_back({name, score});
        }
    }

    void LeaderboardMenu::SaveRecordsToFile(const std::string& filename) const
    {
        std::ofstream fout(filename);
        if (!fout.is_open()) return;
        for (const auto& r : records)
        {
            fout << r.playerName << ' ' << r.score << '\n';
        }
    }

    void LeaderboardMenu::AddRecord(const std::string& filename, const std::string& playerName, int score)
    {
        records.push_back({playerName, score});
        std::sort(records.begin(), records.end(), [](const SLeaderboard& a, const SLeaderboard& b)
        {
            return b.score < a.score; // In descending
        });
        if (records.size() > SETTINGS.SIZE_LEADERBOARD)
            records.resize(SETTINGS.SIZE_LEADERBOARD);
        SaveRecordsToFile(filename);
    }

    void LeaderboardMenu::UpdateRecords(const sf::Font& font)
    {
        records.clear();
        LoadRecordsFromFile(SETTINGS.LEADERBOARD_FILENAME);
        items.clear();
        for (size_t i = 0; i < records.size(); ++i)
        {
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(38);
            t.setFillColor(sf::Color::White);
            t.setString(std::to_string(i + 1) + ". " + records[i].playerName + " - " + std::to_string(records[i].score));
            items.push_back(t);
        }
    }
}
